#include "RenderPanel.hpp"

#include "Application.hpp"
#include "MainFrame.hpp"

#include <Core/Connection.hpp>
#include <Core/Device.hpp>
#include <Core/RenderingResources.hpp>
#include <RenderPass/FrameBuffer.hpp>
#include <RenderPass/RenderPass.hpp>
#include <RenderPass/RenderSubpass.hpp>
#include <RenderPass/RenderSubpassState.hpp>

#include <Transform.hpp>

#include <chrono>

namespace vkapp
{
	namespace
	{
		enum class Ids
		{
			This = 41,
			RenderTimer = 42
		};

		static int const TimerTimeMs = 40;
	}

	RenderPanel::RenderPanel( wxWindow * parent
		, wxSize const & size
		, ashes::Renderer const & renderer )
		: wxPanel{ parent, wxID_ANY, wxDefaultPosition, size }
		, m_timer{ new wxTimer{ this, int( Ids::RenderTimer ) } }
	{
		try
		{
			doCreateDevice( renderer );
			std::cout << "Logical device created." << std::endl;
			doCreateSwapChain();
			std::cout << "Swap chain created." << std::endl;
			doCreateRenderPass();
			std::cout << "Render pass created." << std::endl;
			doPrepareFrames();
			std::cout << "Frames prepared." << std::endl;
		}
		catch ( std::exception & )
		{
			doCleanup();
			throw;
		}

		m_timer->Start( TimerTimeMs );

		Connect( int( Ids::RenderTimer ), wxEVT_TIMER, wxTimerEventHandler( RenderPanel::onTimer ), nullptr, this );
		Connect( wxID_ANY, wxEVT_SIZE, wxSizeEventHandler( RenderPanel::onSize ), nullptr, this );
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
			m_device->waitIdle();
			m_commandBuffers.clear();
			m_swapChain.reset();
			m_frameBuffers.clear();
			m_renderPass.reset();
			m_device.reset();
		}
	}

	void RenderPanel::doCreateDevice( ashes::Renderer const & renderer )
	{
		m_device = renderer.createDevice( common::makeConnection( this, renderer ) );
	}

	void RenderPanel::doCreateSwapChain()
	{
		wxSize size{ GetClientSize() };
		m_swapChain = m_device->createSwapChain( { uint32_t( size.x ), uint32_t( size.y ) } );
		m_swapChain->setClearColour( ashes::ClearColorValue{ 1.0f, 0.8f, 0.4f, 0.0f } );
		m_swapChainReset = m_swapChain->onReset.connect( [this]()
		{
			doResetSwapChain();
		} );
	}

	void RenderPanel::doCreateRenderPass()
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
		m_renderPass = m_device->createRenderPass( attaches
			, std::move( subpasses )
			, ashes::RenderSubpassState{ ashes::PipelineStageFlag::eBottomOfPipe
				, ashes::AccessFlag::eMemoryRead }
			, ashes::RenderSubpassState{ ashes::PipelineStageFlag::eBottomOfPipe
				, ashes::AccessFlag::eMemoryRead } );
	}

	bool RenderPanel::doPrepareFrames()
	{
		bool result{ true };
		m_commandBuffers = m_swapChain->createCommandBuffers();
		m_frameBuffers = m_swapChain->createFrameBuffers( *m_renderPass );
		wxSize size{ GetClientSize() };

		for ( size_t i = 0u; i < m_commandBuffers.size() && result; ++i )
		{
			auto & frameBuffer = *m_frameBuffers[i];
			auto & commandBuffer = *m_commandBuffers[i];

			commandBuffer.begin( ashes::CommandBufferUsageFlag::eSimultaneousUse );
			commandBuffer.beginRenderPass( *m_renderPass
				, frameBuffer
				, { m_swapChain->getClearColour() }
				, ashes::SubpassContents::eInline );
			commandBuffer.endRenderPass();
			commandBuffer.end();
		}

		return result;
	}

	void RenderPanel::doDraw()
	{
		auto resources = m_swapChain->getResources();

		if ( resources )
		{
			auto before = std::chrono::high_resolution_clock::now();
			auto & queue = m_device->getGraphicsQueue();
			queue.submit( *m_commandBuffers[resources->getBackBuffer()]
				, resources->getImageAvailableSemaphore()
				, ashes::PipelineStageFlag::eColourAttachmentOutput
				, resources->getRenderingFinishedSemaphore()
				, &resources->getFence() );
			m_swapChain->present( *resources );

			auto after = std::chrono::high_resolution_clock::now();
			wxGetApp().updateFps( std::chrono::duration_cast< std::chrono::microseconds >( after - before ) );
		}
		else
		{
			m_timer->Stop();
			std::cerr << "Can't render" << std::endl;
		}
	}

	void RenderPanel::doResetSwapChain()
	{
		doPrepareFrames();
	}

	void RenderPanel::onTimer( wxTimerEvent & event )
	{
		if ( event.GetId() == int( Ids::RenderTimer ) )
		{
			doDraw();
		}
	}

	void RenderPanel::onSize( wxSizeEvent & event )
	{
		m_timer->Stop();
		wxSize size = GetClientSize();
		m_swapChain->reset( { uint32_t( size.x ), uint32_t( size.y ) } );
		m_timer->Start( TimerTimeMs );
		event.Skip();
	}
}
