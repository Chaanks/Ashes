/*
This file belongs to Ashes.
See LICENSE file in root folder
*/
#pragma once

#include "Gl3Renderer/Core/GlContext.hpp"
#include "Gl3Renderer/Core/GlPhysicalDevice.hpp"

#include <Ashes/Buffer/VertexBuffer.hpp>
#include <Ashes/Core/Device.hpp>
#include <Ashes/Miscellaneous/SwapChainCreateInfo.hpp>
#include <Ashes/Pipeline/ColourBlendState.hpp>
#include <Ashes/Pipeline/DepthStencilState.hpp>
#include <Ashes/Pipeline/InputAssemblyState.hpp>
#include <Ashes/Pipeline/MultisampleState.hpp>
#include <Ashes/Pipeline/RasterisationState.hpp>
#include <Ashes/Pipeline/Scissor.hpp>
#include <Ashes/Pipeline/TessellationState.hpp>
#include <Ashes/Pipeline/Viewport.hpp>

namespace gl_renderer
{
	/**
	*\brief
	*	Classe contenant les informations liées au GPU logique.
	*/
	class Device
		: public ashes::Device
	{
	public:
		/**
		*\brief
		*	Constructeur.
		*\param[in] instance
		*	L'instance.
		*\param[in] connection
		*	La connection à l'application.
		*/
		Device( Instance const & instance
			, PhysicalDevice const & gpu
			, Context & context
			, ashes::DeviceCreateInfo createInfos );
		~Device();
		/**
		*\copydoc		ashes::Device::createRenderPass
		*/
		ashes::RenderPassPtr createRenderPass( ashes::RenderPassCreateInfo createInfo )const override;
		/**
		*\copydoc		ashes::Device::createPipelineLayout
		*/
		ashes::PipelineLayoutPtr createPipelineLayout( ashes::DescriptorSetLayoutCRefArray const & setLayouts
			, ashes::PushConstantRangeArray const & pushConstantRanges )const override;
		/**
		*\copydoc		ashes::Device::createDescriptorSetLayout
		*/
		ashes::DescriptorSetLayoutPtr createDescriptorSetLayout( ashes::DescriptorSetLayoutBindingArray bindings )const override;
		/**
		*\copydoc	ashes::Device::createDescriptorPool
		*/
		ashes::DescriptorPoolPtr createDescriptorPool( ashes::DescriptorPoolCreateFlags flags
			, uint32_t maxSets
			, ashes::DescriptorPoolSizeArray poolSizes )const override;
		/**
		*\copydoc	ashes::Device::allocateMemory
		*/
		ashes::DeviceMemoryPtr allocateMemory( ashes::MemoryAllocateInfo allocateInfo )const override;
		/**
		*\copydoc		ashes::Device::createImage
		*/
		ashes::ImagePtr createImage( ashes::ImageCreateInfo const & createInfo )const override;
		/**
		*\copydoc	ashes::Device::getImageSubresourceLayout
		*/
		void getImageSubresourceLayout( ashes::Image const & image
			, ashes::ImageSubresource const & subresource
			, ashes::SubresourceLayout & layout )const override;
		/**
		*\copydoc		ashes::Device::createSampler
		*/
		ashes::SamplerPtr createSampler( ashes::SamplerCreateInfo const & createInfo )const override;
		/**
		*\copydoc		ashes::Device::createBuffer
		*/
		ashes::BufferBasePtr createBuffer( uint32_t size
			, ashes::BufferTargets targets )const override;
		/**
		*\copydoc		ashes::Device::createBufferView
		*/
		ashes::BufferViewPtr createBufferView( ashes::BufferBase const & buffer
			, ashes::Format format
			, uint32_t offset
			, uint32_t range )const override;
		/**
		*\copydoc		ashes::Device::createSwapChain
		*/
		ashes::SwapChainPtr createSwapChain( ashes::SwapChainCreateInfo createInfo )const override;
		/**
		*\copydoc		ashes::Device::createSemaphore
		*/
		ashes::SemaphorePtr createSemaphore()const override;
		/**
		*\copydoc	ashes::Device::createFence
		*/
		ashes::FencePtr createFence( ashes::FenceCreateFlags flags = 0 )const override;
		/**
		*\copydoc	ashes::Device::createEvent
		*/
		ashes::EventPtr createEvent()const override;
		/**
		*\copydoc		ashes::Device::createCommandPool
		*/
		ashes::CommandPoolPtr createCommandPool( uint32_t queueFamilyIndex
			, ashes::CommandPoolCreateFlags const & flags )const override;
		/**
		*\copydoc		ashes::Device::createShaderProgram
		*/
		virtual ashes::ShaderModulePtr createShaderModule( ashes::ShaderStageFlag stage )const override;
		/**
		*\copydoc	ashes::Device::createQueryPool
		*/
		ashes::QueryPoolPtr createQueryPool( ashes::QueryType type
			, uint32_t count
			, ashes::QueryPipelineStatisticFlags pipelineStatistics )const override;
		/**
		*\copydoc	ashes::Device::debugMarkerSetObjectName
		*/
		void debugMarkerSetObjectName( ashes::DebugMarkerObjectNameInfo const & nameInfo )const override;
		/**
		*\copydoc	ashes::Device::getQueue
		*/
		ashes::QueuePtr getQueue( uint32_t familyIndex
			, uint32_t index )const override;
		/**
		*\copydoc	ashes::Device::createQueryPool
		*/
		void waitIdle()const override;
		/**
		*\brief
		*	Echange les tampons.
		*/
		void swapBuffers()const;

		void registerContext( ashes::WindowHandle const & handle )const;
		void unregisterContext( ashes::WindowHandle const & handle )const;

		inline ContextLock getContext()const
		{
			return { *m_currentContext };
		}

		inline void setCurrentFramebuffer( GLuint fbo )const
		{
			m_fbo = fbo;
		}

		inline GLuint getCurrentFramebuffer()const
		{
			return m_fbo;
		}

		inline ashes::Scissor & getCurrentScissor()const
		{
			return m_scissor;
		}

		inline ashes::Viewport & getCurrentViewport()const
		{
			return m_viewport;
		}

		inline ashes::ColourBlendState & getCurrentBlendState()const
		{
			return m_cbState;
		}

		inline ashes::DepthStencilState & getCurrentDepthStencilState()const
		{
			return m_dsState;
		}

		inline ashes::MultisampleState & getCurrentMultisampleState()const
		{
			return m_msState;
		}

		inline ashes::RasterisationState & getCurrentRasterisationState()const
		{
			return m_rsState;
		}

		inline ashes::TessellationState & getCurrentTessellationState()const
		{
			return m_tsState;
		}

		inline ashes::InputAssemblyState & getCurrentInputAssemblyState()const
		{
			return m_iaState;
		}

		inline GLuint & getCurrentProgram()const
		{
			return m_currentProgram;
		}

		inline GeometryBuffers & getEmptyIndexedVao()const
		{
			return *m_dummyIndexed.geometryBuffers;
		}

		inline ashes::BufferBase const & getEmptyIndexedVaoIdx()const
		{
			return m_dummyIndexed.indexBuffer->getBuffer();
		}

		inline GLuint getBlitSrcFbo()const
		{
			return m_blitFbos[0];
		}

		inline GLuint getBlitDstFbo()const
		{
			return m_blitFbos[1];
		}

		bool find( std::string const & name )const;
		bool findAny( ashes::StringArray const & names )const;
		bool findAll( ashes::StringArray const & names )const;

	private:
		void doInitialiseContext( ContextLock const & context )const;
		void doCreateQueues();

	private:
		Instance const & m_instance;
		mutable ContextPtr m_ownContext;
		mutable Context * m_currentContext;
		// Mimic the behavior in Vulkan, when no IBO nor VBO is bound.
		mutable struct
		{
			ashes::BufferPtr< uint32_t > indexBuffer;
			ashes::VertexBufferPtr< int > vertexBuffer;
			GeometryBuffersPtr geometryBuffers;
		} m_dummyIndexed;
		mutable ashes::Scissor m_scissor{ 0, 0, 0, 0 };
		mutable ashes::Viewport m_viewport{ 0, 0, 0, 0 };
		mutable ashes::ColourBlendState m_cbState;
		mutable ashes::DepthStencilState m_dsState;
		mutable ashes::MultisampleState m_msState;
		mutable ashes::RasterisationState m_rsState;
		mutable ashes::TessellationState m_tsState;
		mutable ashes::InputAssemblyState m_iaState;
		using QueueCreateCount = std::pair< ashes::DeviceQueueCreateInfo, uint32_t >;
		std::map< uint32_t, QueueCreateCount > m_queues;
		mutable GLuint m_currentProgram;
		mutable GLuint m_blitFbos[2];
		mutable GLuint m_fbo{ 0u };
	};
}
