/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "Command/VkQueue.hpp"

#include "Command/VkCommandBuffer.hpp"
#include "Core/VkDevice.hpp"
#include "Core/VkSwapChain.hpp"
#include "Sync/VkFence.hpp"
#include "Sync/VkSemaphore.hpp"

namespace vk_renderer
{
	namespace
	{
		CommandBufferCRefArray convert( ashes::CommandBufferCRefArray const & values )
		{
			CommandBufferCRefArray result;
			result.reserve( values.size() );

			for ( auto & value : values )
			{
				result.emplace_back( static_cast< CommandBuffer const & >( value.get() ) );
			}

			return result;
		}

		SemaphoreCRefArray convert( ashes::SemaphoreCRefArray const & values )
		{
			SemaphoreCRefArray result;
			result.reserve( values.size() );

			for ( auto & value : values )
			{
				result.emplace_back( static_cast< Semaphore const & >( value.get() ) );
			}

			return result;
		}

		SwapChainCRefArray convert( ashes::SwapChainCRefArray const & values )
		{
			SwapChainCRefArray result;
			result.reserve( values.size() );

			for ( auto & value : values )
			{
				result.emplace_back( static_cast< SwapChain const & >( value.get() ) );
			}

			return result;
		}
	}

	Queue::Queue( Device const & device
		, ashes::DeviceQueueCreateInfo createInfo
		, uint32_t index )
		: ashes::Queue{ device, std::move( createInfo ), index }
		, m_device{ device }
	{
		m_device.vkGetDeviceQueue( m_device, createInfo.queueFamilyIndex, index, &m_queue );
	}

	void Queue::submit( ashes::CommandBufferCRefArray const & commandBuffers
		, ashes::SemaphoreCRefArray const & semaphoresToWait
		, ashes::PipelineStageFlagsArray const & semaphoresStage
		, ashes::SemaphoreCRefArray const & semaphoresToSignal
		, ashes::Fence const * fence )const
	{
		auto vkcommandBuffers = makeVkArray< VkCommandBuffer >( convert( commandBuffers ) );
		auto vksemaphoresToWait = makeVkArray< VkSemaphore >( convert( semaphoresToWait ) );
		auto vksemaphoresToSignal = makeVkArray< VkSemaphore >( convert( semaphoresToSignal ) );
		auto vksemaphoresStage = convert< VkPipelineStageFlags >( semaphoresStage );

		std::vector< VkSubmitInfo > submitInfo
		{
			{
				VK_STRUCTURE_TYPE_SUBMIT_INFO,
				nullptr,
				static_cast< uint32_t >( vksemaphoresToWait.size() ),      // waitSemaphoreCount
				vksemaphoresToWait.empty()                                 // pWaitSemaphores
					? nullptr
					: vksemaphoresToWait.data(),
				vksemaphoresStage.empty()                                  // pWaitDstStageMask
					? nullptr
					: vksemaphoresStage.data(),
				static_cast< uint32_t >( vkcommandBuffers.size() ),        // commandBufferCount
				vkcommandBuffers.empty()                                   // pCommandBuffers
					? nullptr
					: vkcommandBuffers.data(),
				static_cast< uint32_t >( vksemaphoresToSignal.size() ),    // signalSemaphoreCount
				vksemaphoresToSignal.empty()                               // pSignalSemaphores
					? nullptr
					: vksemaphoresToSignal.data()
			}
		};
		DEBUG_DUMP( submitInfo );
		auto res = m_device.vkQueueSubmit( m_queue
			, static_cast< uint32_t >( submitInfo.size() )
			, submitInfo.data()
			, fence ? static_cast< VkFence const & >( *static_cast< Fence const * >( fence ) ) : VK_NULL_HANDLE );
		checkError( res, "Queue submit" );
	}

	ashes::ResultArray Queue::present( ashes::SwapChainCRefArray const & swapChains
		, ashes::UInt32Array const & imagesIndex
		, ashes::SemaphoreCRefArray const & semaphoresToWait )const
	{
		assert( swapChains.size() == imagesIndex.size() );
		auto vkswapchains = makeVkArray< VkSwapchainKHR, SwapChain >( swapChains );
		auto vksemaphoresToWait = makeVkArray< VkSemaphore, Semaphore >( semaphoresToWait );
		std::vector< VkResult > results;
		results.resize( swapChains.size() );
		VkPresentInfoKHR presentInfo
		{
			VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
			nullptr,
			static_cast< uint32_t >( vksemaphoresToWait.size() ),    // waitSemaphoreCount
			vksemaphoresToWait.data(),                               // pWaitSemaphores
			static_cast< uint32_t >( imagesIndex.size() ),           // swapchainCount
			vkswapchains.data(),                                     // pSwapchains
			imagesIndex.data(),                                      // pImageIndices
			results.data()                                           // pResults
		};
		DEBUG_DUMP( presentInfo );
		checkError( m_device.vkQueuePresentKHR( m_queue, &presentInfo )
			, "Queue present" );
		return convert< ashes::Result >( results );
	}

	void Queue::waitIdle()const
	{
		auto res = m_device.vkQueueWaitIdle( m_queue );
		checkError( res, "Queue wait idle" );
	}
}
