#include "RenderPanel.hpp"

#include "Application.hpp"
#include "EquirectangularToCube.hpp"
#include "MainFrame.hpp"

#include <Buffer/StagingBuffer.hpp>
#include <Buffer/UniformBuffer.hpp>
#include <Buffer/VertexBuffer.hpp>
#include <Command/Queue.hpp>
#include <Core/Surface.hpp>
#include <Core/Device.hpp>
#include <Core/Instance.hpp>
#include <Core/SwapChain.hpp>
#include <Descriptor/DescriptorSet.hpp>
#include <Descriptor/DescriptorSetLayout.hpp>
#include <Descriptor/DescriptorSetLayoutBinding.hpp>
#include <Descriptor/DescriptorSetPool.hpp>
#include <Image/Image.hpp>
#include <Image/ImageView.hpp>
#include <Miscellaneous/QueryPool.hpp>
#include <Pipeline/DepthStencilState.hpp>
#include <Pipeline/InputAssemblyState.hpp>
#include <Pipeline/MultisampleState.hpp>
#include <Pipeline/Scissor.hpp>
#include <Pipeline/VertexLayout.hpp>
#include <Pipeline/Viewport.hpp>
#include <RenderPass/FrameBuffer.hpp>
#include <RenderPass/RenderPass.hpp>
#include <RenderPass/RenderSubpass.hpp>
#include <RenderPass/RenderSubpassState.hpp>
#include <GlslToSpv.hpp>
#include <Sync/ImageMemoryBarrier.hpp>

#include <Transform.hpp>

#include <FileUtils.hpp>

#include <chrono>

namespace vkapp
{
	namespace
	{
		enum class Ids
		{
			RenderTimer = 42
		}	Ids;

		static int const TimerTimeMs = 20;
	}

	RenderPanel::RenderPanel( wxWindow * parent
		, wxSize const & size
		, utils::Instance const & instance )
		: wxPanel{ parent, wxID_ANY, wxDefaultPosition, size }
		, m_timer{ new wxTimer{ this, int( Ids::RenderTimer ) } }
		, m_offscreenVertexData
		{
			// Front
			{ { -1.0, -1.0, +1.0, 1.0 }, { 0.0, 0.0 } },
			{ { -1.0, +1.0, +1.0, 1.0 }, { 0.0, 1.0 } },
			{ { +1.0, -1.0, +1.0, 1.0 }, { 1.0, 0.0 } },
			{ { +1.0, +1.0, +1.0, 1.0 }, { 1.0, 1.0 } },
			// Top
			{ { -1.0, +1.0, +1.0, 1.0 }, { 0.0, 0.0 } },
			{ { -1.0, +1.0, -1.0, 1.0 }, { 0.0, 1.0 } },
			{ { +1.0, +1.0, +1.0, 1.0 }, { 1.0, 0.0 } },
			{ { +1.0, +1.0, -1.0, 1.0 }, { 1.0, 1.0 } },
			// Back
			{ { -1.0, +1.0, -1.0, 1.0 }, { 1.0, 1.0 } },
			{ { -1.0, -1.0, -1.0, 1.0 }, { 1.0, 0.0 } },
			{ { +1.0, +1.0, -1.0, 1.0 }, { 0.0, 1.0 } },
			{ { +1.0, -1.0, -1.0, 1.0 }, { 0.0, 0.0 } },
			// Bottom
			{ { -1.0, -1.0, -1.0, 1.0 }, { 1.0, 1.0 } },
			{ { -1.0, -1.0, +1.0, 1.0 }, { 1.0, 0.0 } },
			{ { +1.0, -1.0, -1.0, 1.0 }, { 0.0, 1.0 } },
			{ { +1.0, -1.0, +1.0, 1.0 }, { 0.0, 0.0 } },
			// Right
			{ { +1.0, -1.0, +1.0, 1.0 }, { 0.0, 0.0 } },
			{ { +1.0, +1.0, +1.0, 1.0 }, { 0.0, 1.0 } },
			{ { +1.0, -1.0, -1.0, 1.0 }, { 1.0, 0.0 } },
			{ { +1.0, +1.0, -1.0, 1.0 }, { 1.0, 1.0 } },
			// Left
			{ { -1.0, -1.0, -1.0, 1.0 }, { 0.0, 0.0 } },
			{ { -1.0, +1.0, -1.0, 1.0 }, { 0.0, 1.0 } },
			{ { -1.0, -1.0, +1.0, 1.0 }, { 1.0, 0.0 } },
			{ { -1.0, +1.0, +1.0, 1.0 }, { 1.0, 1.0 } },
		}
		, m_offscreenIndexData
		{
			// Front
			0, 1, 2, 2, 1, 3,
			// Top
			4, 5, 6, 6, 5, 7,
			// Back
			8, 9, 10, 10, 9, 11,
			// Bottom
			12, 13, 14, 14, 13, 15,
			// Right
			16, 17, 18, 18, 17, 19,
			// Left
			20, 21, 22, 22, 21, 23,
		}
		, m_mainVertexData
		{
			{ { -1.0, -1.0, 0.0, 1.0 }, { 0.0, 0.0 } },
			{ { -1.0, +1.0, 0.0, 1.0 }, { 0.0, 1.0 } },
			{ { +1.0, -1.0, 0.0, 1.0 }, { 1.0, 0.0 } },
			{ { +1.0, +1.0, 0.0, 1.0 }, { 1.0, 1.0 } },
		}
	{
		try
		{
			auto surface = doCreateSurface( instance );
			std::cout << "Surface created." << std::endl;
			doCreateDevice( instance, *surface );
			std::cout << "Logical device created." << std::endl;
			doCreateSwapChain( std::move( surface ) );
			std::cout << "Swap chain created." << std::endl;
			doCreateStagingBuffer();
			std::cout << "Staging buffer created." << std::endl;
			doCreateTexture();
			std::cout << "Truck texture created." << std::endl;
			doCreateUniformBuffer();
			std::cout << "Uniform buffer created." << std::endl;
			doCreateOffscreenDescriptorSet();
			std::cout << "Offscreen descriptor set created." << std::endl;
			doCreateOffscreenRenderPass();
			std::cout << "Offscreen render pass created." << std::endl;
			doCreateFrameBuffer();
			std::cout << "Frame buffer created." << std::endl;
			doCreateOffscreenVertexBuffer();
			std::cout << "Offscreen vertex buffer created." << std::endl;
			doCreateOffscreenPipeline();
			std::cout << "Offscreen pipeline created." << std::endl;
			doPrepareOffscreenFrame();
			doCreateMainDescriptorSet();
			std::cout << "Main descriptor set created." << std::endl;
			doCreateMainRenderPass();
			std::cout << "Main render pass created." << std::endl;
			doCreateMainVertexBuffer();
			std::cout << "Main vertex buffer created." << std::endl;
			doCreateMainPipeline();
			std::cout << "Main pipeline created." << std::endl;
			doPrepareMainFrames();
		}
		catch ( std::exception & )
		{
			doCleanup();
			throw;
		}

		m_timer->Start( TimerTimeMs );

		Connect( int( Ids::RenderTimer )
			, wxEVT_TIMER
			, wxTimerEventHandler( RenderPanel::onTimer )
			, nullptr
			, this );
		Connect( wxID_ANY
			, wxEVT_SIZE
			, wxSizeEventHandler( RenderPanel::onSize )
			, nullptr
			, this );
	}

	RenderPanel::~RenderPanel()
	{
		doCleanup();
	}

	void RenderPanel::doCleanup()
	{
		delete m_timer;

		if ( m_device )
		{
			m_device->getDevice().waitIdle();
			m_equiToCube.reset();

			m_commandBuffer.reset();
			m_commandBuffers.clear();
			m_frameBuffers.clear();
			m_sampler.reset();
			m_view.reset();
			m_texture.reset();
			m_stagingBuffer.reset();

			m_matrixUbo.reset();
			m_objectUbo.reset();
			m_mainDescriptorSet.reset();
			m_mainDescriptorPool.reset();
			m_mainDescriptorLayout.reset();
			m_mainPipeline.reset();
			m_mainPipelineLayout.reset();
			m_mainVertexBuffer.reset();
			m_mainRenderPass.reset();

			m_queryPool.reset();
			m_offscreenDescriptorSet.reset();
			m_offscreenDescriptorPool.reset();
			m_offscreenDescriptorLayout.reset();
			m_offscreenPipeline.reset();
			m_offscreenPipelineLayout.reset();
			m_offscreenIndexBuffer.reset();
			m_offscreenVertexBuffer.reset();
			m_offscreenRenderPass.reset();

			m_frameBuffer.reset();
			m_renderTargetColour.reset();

			m_swapChain.reset();
			m_commandPool.reset();
			m_presentQueue.reset();
			m_graphicsQueue.reset();
			m_device.reset();
		}
	}

	void RenderPanel::doUpdateProjection()
	{
		auto size = m_swapChain->getDimensions();
		auto width = float( size.width );
		auto height = float( size.height );
		auto ratio = width / height;
		m_matrixUbo->getData( 0u ) = utils::Mat4{ m_device->getDevice().perspective( float( utils::toRadians( 90.0_degrees ) / ratio )
			, width / height
			, 0.01f
			, 100.0f ) };
		m_stagingBuffer->uploadUniformData( *m_graphicsQueue
			, *m_commandPool
			, m_matrixUbo->getDatas()
			, *m_matrixUbo
			, ashes::PipelineStageFlag::eVertexShader );
	}

	ashes::SurfacePtr RenderPanel::doCreateSurface( utils::Instance const & instance )
	{
		auto handle = common::makeWindowHandle( *this );
		auto & gpu = instance.getPhysicalDevice( 0u );
		return instance.getInstance().createSurface( gpu
			, std::move( handle ) );
	}

	void RenderPanel::doCreateDevice( utils::Instance const & instance
		, ashes::Surface const & surface )
	{
		m_device = std::make_unique< utils::Device >( instance.getInstance()
			, surface );
		m_graphicsQueue = m_device->getDevice().getQueue( m_device->getGraphicsQueueFamily(), 0u );
		m_presentQueue = m_device->getDevice().getQueue( m_device->getPresentQueueFamily(), 0u );
		m_commandPool = m_device->getDevice().createCommandPool( m_device->getGraphicsQueueFamily()
			, ashes::CommandPoolCreateFlag::eResetCommandBuffer | ashes::CommandPoolCreateFlag::eTransient );
	}

	void RenderPanel::doCreateSwapChain( ashes::SurfacePtr surface )
	{
		wxSize size{ GetClientSize() };
		m_swapChain = std::make_unique< utils::SwapChain >( m_device->getDevice()
			, *m_commandPool
			, std::move( surface )
			, ashes::Extent2D{ uint32_t( size.x ), uint32_t( size.y ) } );
		m_clearColour = ashes::ClearColorValue{ 1.0f, 0.8f, 0.4f, 0.0f };
		m_swapChainReset = m_swapChain->onReset.connect( [this]()
		{
			doCreateFrameBuffer();
			doPrepareOffscreenFrame();
			doCreateMainDescriptorSet();
			doPrepareMainFrames();
		} );
	}

	void RenderPanel::doCreateTexture()
	{
		m_texture = m_device->createImage(
			{
				ashes::ImageCreateFlag::eCubeCompatible,
				ashes::ImageType::e2D,
				ashes::Format::eR8G8B8A8_UNORM,
				{ 512u, 512u, 1u },
				1u,
				6u,
				ashes::SampleCountFlag::e1,
				ashes::ImageTiling::eOptimal,
				ashes::ImageUsageFlag::eColourAttachment | ashes::ImageUsageFlag::eSampled
			}
			, ashes::MemoryPropertyFlag::eDeviceLocal );
		std::string shadersFolder = utils::getPath( utils::getExecutableDirectory() ) / "share" / "Assets";
		m_equiToCube = std::make_shared< EquirectangularToCube >( shadersFolder / "BasketballCourt_4k.jpg"
			, *m_device
			, *m_graphicsQueue
			, *m_commandPool
			, *m_texture );
		m_equiToCube->render();

		m_view = m_texture->createView( ashes::ImageViewType::eCube
			, ashes::Format::eR8G8B8A8_UNORM
			, 0u
			, 1u
			, 0u
			, 6u );
		m_sampler = m_device->getDevice().createSampler( ashes::WrapMode::eClampToEdge
			, ashes::WrapMode::eClampToEdge
			, ashes::WrapMode::eClampToEdge
			, ashes::Filter::eLinear
			, ashes::Filter::eLinear );
	}

	void RenderPanel::doCreateUniformBuffer()
	{
		m_matrixUbo = utils::makeUniformBuffer< utils::Mat4 >( *m_device
			, 1u
			, ashes::BufferTarget::eTransferDst
			, ashes::MemoryPropertyFlag::eDeviceLocal );
		m_objectUbo = utils::makeUniformBuffer< utils::Mat4 >( *m_device
			, 1u
			, ashes::BufferTarget::eTransferDst
			, ashes::MemoryPropertyFlag::eDeviceLocal );
	}

	void RenderPanel::doCreateStagingBuffer()
	{
		m_stagingBuffer = std::make_unique< ashes::StagingBuffer >( m_device->getDevice()
			, 0u
			, 20000000u );
	}

	void RenderPanel::doCreateOffscreenDescriptorSet()
	{
		std::vector< ashes::DescriptorSetLayoutBinding > bindings
		{
			ashes::DescriptorSetLayoutBinding{ 0u, ashes::DescriptorType::eCombinedImageSampler, ashes::ShaderStageFlag::eFragment },
			ashes::DescriptorSetLayoutBinding{ 1u, ashes::DescriptorType::eUniformBuffer, ashes::ShaderStageFlag::eVertex },
			ashes::DescriptorSetLayoutBinding{ 2u, ashes::DescriptorType::eUniformBuffer, ashes::ShaderStageFlag::eVertex },
		};
		m_offscreenDescriptorLayout = m_device->getDevice().createDescriptorSetLayout( std::move( bindings ) );
		m_offscreenDescriptorPool = m_offscreenDescriptorLayout->createPool( 1u );
		m_offscreenDescriptorSet = m_offscreenDescriptorPool->createDescriptorSet();
		m_offscreenDescriptorSet->createBinding( m_offscreenDescriptorLayout->getBinding( 0u )
			, *m_view
			, *m_sampler );
		m_offscreenDescriptorSet->createBinding( m_offscreenDescriptorLayout->getBinding( 1u )
			, *m_matrixUbo
			, 0u
			, 1u );
		m_offscreenDescriptorSet->createBinding( m_offscreenDescriptorLayout->getBinding( 2u )
			, *m_objectUbo
			, 0u
			, 1u );
		m_offscreenDescriptorSet->update();
	}

	void RenderPanel::doCreateOffscreenRenderPass()
	{
		ashes::AttachmentDescriptionArray attaches
		{
			{
				ashes::Format::eR8G8B8A8_UNORM,
				ashes::SampleCountFlag::e1,
				ashes::AttachmentLoadOp::eClear,
				ashes::AttachmentStoreOp::eStore,
				ashes::AttachmentLoadOp::eDontCare,
				ashes::AttachmentStoreOp::eDontCare,
				ashes::ImageLayout::eUndefined,
				ashes::ImageLayout::eShaderReadOnlyOptimal,
			}
		};
		ashes::AttachmentReferenceArray subAttaches
		{
			{ 0u, ashes::ImageLayout::eColourAttachmentOptimal }
		};
		ashes::RenderSubpassPtrArray subpasses;
		subpasses.emplace_back( std::make_unique< ashes::RenderSubpass >( ashes::PipelineBindPoint::eGraphics
			, ashes::RenderSubpassState{ ashes::PipelineStageFlag::eColourAttachmentOutput
				, ashes::AccessFlag::eColourAttachmentWrite }
			, subAttaches ) );
		m_offscreenRenderPass = m_device->getDevice().createRenderPass( attaches
			, std::move( subpasses )
			, ashes::RenderSubpassState{ ashes::PipelineStageFlag::eColourAttachmentOutput
				, ashes::AccessFlag::eColourAttachmentWrite }
			, ashes::RenderSubpassState{ ashes::PipelineStageFlag::eColourAttachmentOutput
				, ashes::AccessFlag::eShaderRead } );
	}

	void RenderPanel::doCreateFrameBuffer()
	{
		auto size = GetClientSize();
		m_renderTargetColour = m_device->createImage(
			{
				0u,
				ashes::ImageType::e2D,
				ashes::Format::eR8G8B8A8_UNORM,
				{ uint32_t( size.GetWidth() ), uint32_t( size.GetHeight() ), 1u },
				1u,
				1u,
				ashes::SampleCountFlag::e1,
				ashes::ImageTiling::eOptimal,
				ashes::ImageUsageFlag::eColourAttachment | ashes::ImageUsageFlag::eSampled
			}
			, ashes::MemoryPropertyFlag::eDeviceLocal );
		ashes::FrameBufferAttachmentArray attaches;
		attaches.emplace_back( *( m_offscreenRenderPass->getAttachments().begin() + 0u )
			, m_renderTargetColour->createView( ashes::ImageViewType::e2D
				, m_renderTargetColour->getFormat() ) );
		m_frameBuffer = m_offscreenRenderPass->createFrameBuffer( { uint32_t( size.GetWidth() ), uint32_t( size.GetHeight() ) }
			, std::move( attaches ) );
	}

	void RenderPanel::doCreateOffscreenVertexBuffer()
	{
		m_offscreenVertexLayout = ashes::makeLayout< TexturedVertexData >( 0 );
		m_offscreenVertexLayout->createAttribute( 0u
			, ashes::Format::eR32G32B32A32_SFLOAT
			, uint32_t( offsetof( TexturedVertexData, position ) ) );
		m_offscreenVertexLayout->createAttribute( 1u
			, ashes::Format::eR32G32_SFLOAT
			, uint32_t( offsetof( TexturedVertexData, uv ) ) );

		m_offscreenVertexBuffer = utils::makeVertexBuffer< TexturedVertexData >( *m_device
			, uint32_t( m_offscreenVertexData.size() )
			, ashes::BufferTarget::eTransferDst
			, ashes::MemoryPropertyFlag::eDeviceLocal );
		m_stagingBuffer->uploadVertexData( *m_graphicsQueue
			, *m_commandPool
			, m_offscreenVertexData
			, *m_offscreenVertexBuffer );

		m_offscreenIndexBuffer = utils::makeBuffer< uint16_t >( *m_device
			, uint32_t( m_offscreenIndexData.size() )
			, ashes::BufferTarget::eIndexBuffer | ashes::BufferTarget::eTransferDst
			, ashes::MemoryPropertyFlag::eDeviceLocal );
		m_stagingBuffer->uploadBufferData( *m_graphicsQueue
			, *m_commandPool
			, m_offscreenIndexData
			, *m_offscreenIndexBuffer );
	}

	void RenderPanel::doCreateOffscreenPipeline()
	{
		m_offscreenPipelineLayout = m_device->getDevice().createPipelineLayout( *m_offscreenDescriptorLayout );
		wxSize size{ GetClientSize() };
		std::string shadersFolder = utils::getPath( utils::getExecutableDirectory() ) / "share" / AppName / "Shaders";

		if ( !wxFileExists( shadersFolder / "offscreen.vert" )
			|| !wxFileExists( shadersFolder / "offscreen.frag" ) )
		{
			throw std::runtime_error{ "Shader files are missing" };
		}

		std::vector< ashes::ShaderStageState > shaderStages;
		shaderStages.push_back( { m_device->getDevice().createShaderModule( ashes::ShaderStageFlag::eVertex ) } );
		shaderStages.push_back( { m_device->getDevice().createShaderModule( ashes::ShaderStageFlag::eFragment ) } );
		shaderStages[0].module->loadShader( common::parseShaderFile( m_device->getDevice()
			, ashes::ShaderStageFlag::eVertex
			, shadersFolder / "offscreen.vert" ) );
		shaderStages[1].module->loadShader( common::parseShaderFile( m_device->getDevice()
			, ashes::ShaderStageFlag::eFragment
			, shadersFolder / "offscreen.frag" ) );

		ashes::RasterisationState rasterisationState;
		rasterisationState.cullMode = ashes::CullModeFlag::eNone;

		m_offscreenPipeline = m_offscreenPipelineLayout->createPipeline( ashes::GraphicsPipelineCreateInfo
		{
			std::move( shaderStages ),
			*m_offscreenRenderPass,
			ashes::VertexInputState::create( *m_offscreenVertexLayout ),
			ashes::InputAssemblyState{ ashes::PrimitiveTopology::eTriangleList },
			rasterisationState,
			ashes::MultisampleState{},
			ashes::ColourBlendState::createDefault(),
			{ ashes::DynamicStateEnable::eViewport, ashes::DynamicStateEnable::eScissor }
		} );
	}

	void RenderPanel::doCreateMainDescriptorSet()
	{
		std::vector< ashes::DescriptorSetLayoutBinding > bindings
		{
			ashes::DescriptorSetLayoutBinding{ 0u, ashes::DescriptorType::eCombinedImageSampler, ashes::ShaderStageFlag::eFragment },
		};
		m_mainDescriptorLayout = m_device->getDevice().createDescriptorSetLayout( std::move( bindings ) );
		m_mainDescriptorSet.reset();
		m_mainDescriptorPool = m_mainDescriptorLayout->createPool( 1u );
		m_mainDescriptorSet = m_mainDescriptorPool->createDescriptorSet();
		m_mainDescriptorSet->createBinding( m_mainDescriptorLayout->getBinding( 0u )
			, m_frameBuffer->begin()->getView()
			, *m_sampler );
		m_mainDescriptorSet->update();
	}

	void RenderPanel::doCreateMainRenderPass()
	{
		ashes::AttachmentDescriptionArray attaches
		{
			{
				m_swapChain->getFormat(),
				ashes::SampleCountFlag::e1,
				ashes::AttachmentLoadOp::eClear,
				ashes::AttachmentStoreOp::eStore,
				ashes::AttachmentLoadOp::eDontCare,
				ashes::AttachmentStoreOp::eDontCare,
				ashes::ImageLayout::eUndefined,
				ashes::ImageLayout::ePresentSrc,
			}
		};
		ashes::AttachmentReferenceArray subAttaches
		{
			{ 0u, ashes::ImageLayout::eColourAttachmentOptimal }
		};
		ashes::RenderSubpassPtrArray subpasses;
		subpasses.emplace_back( std::make_unique< ashes::RenderSubpass >( ashes::PipelineBindPoint::eGraphics
			, ashes::RenderSubpassState{ ashes::PipelineStageFlag::eColourAttachmentOutput
				, ashes::AccessFlag::eColourAttachmentWrite }
			, subAttaches ) );
		m_mainRenderPass = m_device->getDevice().createRenderPass( attaches
			, std::move( subpasses )
			, ashes::RenderSubpassState{ ashes::PipelineStageFlag::eBottomOfPipe
				, ashes::AccessFlag::eMemoryRead }
			, ashes::RenderSubpassState{ ashes::PipelineStageFlag::eBottomOfPipe
				, ashes::AccessFlag::eMemoryRead } );
	}

	void RenderPanel::doPrepareOffscreenFrame()
	{
		doUpdateProjection();
		m_queryPool = m_device->getDevice().createQueryPool( ashes::QueryType::eTimestamp
			, 2u
			, 0u );
		m_commandBuffer = m_commandPool->createCommandBuffer();
		wxSize size{ GetClientSize() };
		auto & commandBuffer = *m_commandBuffer;
		auto & frameBuffer = *m_frameBuffer;

		commandBuffer.begin( ashes::CommandBufferUsageFlag::eSimultaneousUse );
		auto dimensions = m_swapChain->getDimensions();
		commandBuffer.resetQueryPool( *m_queryPool
			, 0u
			, 2u );
		commandBuffer.beginRenderPass( *m_offscreenRenderPass
			, frameBuffer
			, { ashes::ClearValue{ m_clearColour } }
			, ashes::SubpassContents::eInline );
		commandBuffer.writeTimestamp( ashes::PipelineStageFlag::eTopOfPipe
			, *m_queryPool
			, 0u );
		commandBuffer.bindPipeline( *m_offscreenPipeline );
		commandBuffer.setViewport( { dimensions.width, dimensions.height, 0, 0 } );
		commandBuffer.setScissor( { 0, 0, dimensions.width, dimensions.height } );
		commandBuffer.bindVertexBuffer( 0u, m_offscreenVertexBuffer->getBuffer(), 0u );
		commandBuffer.bindIndexBuffer( m_offscreenIndexBuffer->getBuffer(), 0u, ashes::IndexType::eUInt16 );
		commandBuffer.bindDescriptorSet( *m_offscreenDescriptorSet
			, *m_offscreenPipelineLayout );
		commandBuffer.drawIndexed( uint32_t( m_offscreenIndexData.size() ) );
		commandBuffer.writeTimestamp( ashes::PipelineStageFlag::eBottomOfPipe
			, *m_queryPool
			, 1u );
		commandBuffer.endRenderPass();
		commandBuffer.end();
	}

	void RenderPanel::doCreateMainVertexBuffer()
	{
		m_mainVertexLayout = ashes::makeLayout< TexturedVertexData >( 0 );
		m_mainVertexLayout->createAttribute( 0u
			, ashes::Format::eR32G32B32A32_SFLOAT
			, uint32_t( offsetof( TexturedVertexData, position ) ) );
		m_mainVertexLayout->createAttribute( 1u
			, ashes::Format::eR32G32_SFLOAT
			, uint32_t( offsetof( TexturedVertexData, uv ) ) );

		m_mainVertexBuffer = utils::makeVertexBuffer< TexturedVertexData >( *m_device
			, uint32_t( m_mainVertexData.size() )
			, ashes::BufferTarget::eTransferDst
			, ashes::MemoryPropertyFlag::eDeviceLocal );
		m_stagingBuffer->uploadVertexData( *m_graphicsQueue
			, *m_commandPool
			, m_mainVertexData
			, *m_mainVertexBuffer );
	}

	void RenderPanel::doCreateMainPipeline()
	{
		m_mainPipelineLayout = m_device->getDevice().createPipelineLayout( *m_mainDescriptorLayout );
		wxSize size{ GetClientSize() };
		std::string shadersFolder = utils::getPath( utils::getExecutableDirectory() ) / "share" / AppName / "Shaders";

		if ( !wxFileExists( shadersFolder / "main.vert" )
			|| !wxFileExists( shadersFolder / "main.frag" ) )
		{
			throw std::runtime_error{ "Shader files are missing" };
		}

		std::vector< ashes::ShaderStageState > shaderStages;
		shaderStages.push_back( { m_device->getDevice().createShaderModule( ashes::ShaderStageFlag::eVertex ) } );
		shaderStages.push_back( { m_device->getDevice().createShaderModule( ashes::ShaderStageFlag::eFragment ) } );
		shaderStages[0].module->loadShader( common::parseShaderFile( m_device->getDevice()
			, ashes::ShaderStageFlag::eVertex
			, shadersFolder / "main.vert" ) );
		shaderStages[1].module->loadShader( common::parseShaderFile( m_device->getDevice()
			, ashes::ShaderStageFlag::eFragment
			, shadersFolder / "main.frag" ) );

		m_mainPipeline = m_mainPipelineLayout->createPipeline( ashes::GraphicsPipelineCreateInfo
		{
			std::move( shaderStages ),
			*m_mainRenderPass,
			ashes::VertexInputState::create( *m_mainVertexLayout ),
			ashes::InputAssemblyState{ ashes::PrimitiveTopology::eTriangleStrip },
			ashes::RasterisationState{},
			ashes::MultisampleState{},
			ashes::ColourBlendState::createDefault(),
			{ ashes::DynamicStateEnable::eViewport, ashes::DynamicStateEnable::eScissor }
		} );
	}

	void RenderPanel::doPrepareMainFrames()
	{
		m_frameBuffers = m_swapChain->createFrameBuffers( *m_mainRenderPass );
		m_commandBuffers = m_swapChain->createCommandBuffers();

		for ( size_t i = 0u; i < m_frameBuffers.size(); ++i )
		{
			auto & frameBuffer = *m_frameBuffers[i];
			auto & commandBuffer = *m_commandBuffers[i];

			wxSize size{ GetClientSize() };

			commandBuffer.begin( ashes::CommandBufferUsageFlag::eSimultaneousUse );
			auto dimensions = m_swapChain->getDimensions();
			commandBuffer.beginRenderPass( *m_mainRenderPass
				, frameBuffer
				, { ashes::ClearValue{ { 1.0, 0.0, 0.0, 1.0 } } }
				, ashes::SubpassContents::eInline );
			commandBuffer.bindPipeline( *m_mainPipeline );
			commandBuffer.setViewport( { dimensions.width
				, dimensions.height
				, 0
				, 0 } );
			commandBuffer.setScissor( { 0
				, 0
				, dimensions.width
				, dimensions.height } );
			commandBuffer.bindVertexBuffer( 0u, m_mainVertexBuffer->getBuffer(), 0u );
			commandBuffer.bindDescriptorSet( *m_mainDescriptorSet
				, *m_mainPipelineLayout );
			commandBuffer.draw( 4u );
			commandBuffer.endRenderPass();

			commandBuffer.end();
		}
	}

	void RenderPanel::doUpdate()
	{
		static utils::Mat4 const originalRotate = []()
		{
			utils::Mat4 result;
			result = utils::rotate( result
				, float( utils::DegreeToRadian * 45.0 )
				, { 0, 0, 1 } );
			return result;
		}();
		m_rotate = utils::rotate( m_rotate
			, float( utils::DegreeToRadian )
			, { 0, 1, 0 } );
		m_objectUbo->getData( 0 ) = m_rotate * originalRotate;
		m_stagingBuffer->uploadUniformData( *m_graphicsQueue
			, *m_commandPool
			, m_objectUbo->getDatas()
			, *m_objectUbo
			, ashes::PipelineStageFlag::eVertexShader );
		std::string shadersFolder = utils::getPath( utils::getExecutableDirectory() ) / "share" / "Assets";
	}

	void RenderPanel::doDraw()
	{
		auto resources = m_swapChain->getResources();

		if ( resources )
		{
			auto before = std::chrono::high_resolution_clock::now();
			m_graphicsQueue->submit( *m_commandBuffer
				, nullptr );
			m_graphicsQueue->waitIdle();

			m_graphicsQueue->submit( *m_commandBuffers[resources->getImageIndex()]
				, resources->getImageAvailableSemaphore()
				, ashes::PipelineStageFlag::eColourAttachmentOutput
				, resources->getRenderingFinishedSemaphore()
				, &resources->getFence() );
			m_swapChain->present( *resources, *m_presentQueue );
			ashes::UInt64Array values{ 0u, 0u };
			m_queryPool->getResults( 0u
				, 2u
				, 0u
				, ashes::QueryResultFlag::eWait
				, values );

			// Elapsed time in nanoseconds
			auto elapsed = std::chrono::nanoseconds{ uint64_t( ( values[1] - values[0] ) / float( m_device->getDevice().getTimestampPeriod() ) ) };
			auto after = std::chrono::high_resolution_clock::now();
			wxGetApp().updateFps( std::chrono::duration_cast< std::chrono::microseconds >( elapsed )
				, std::chrono::duration_cast< std::chrono::microseconds >( after - before ) );
		}
		else
		{
			m_timer->Stop();
		}
	}

	void RenderPanel::doResetSwapChain()
	{
		m_device->getDevice().waitIdle();
		wxSize size{ GetClientSize() };
		m_swapChain->reset( { uint32_t( size.GetWidth() ), uint32_t( size.GetHeight() ) } );
	}

	void RenderPanel::onTimer( wxTimerEvent & event )
	{
		if ( event.GetId() == int( Ids::RenderTimer ) )
		{
			doUpdate();
			doDraw();
		}
	}

	void RenderPanel::onSize( wxSizeEvent & event )
	{
		m_timer->Stop();
		doResetSwapChain();
		m_timer->Start( TimerTimeMs );
		event.Skip();
	}
}
