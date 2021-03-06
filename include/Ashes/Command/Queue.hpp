/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___Ashes_Queue_HPP___
#define ___Ashes_Queue_HPP___
#pragma once

#include "Ashes/AshesPrerequisites.hpp"
#include "Ashes/Miscellaneous/QueueCreateInfo.hpp"

namespace ashes
{
	/**
	*\~french
	*\brief
	*	File de tampons de commandes.
	*\~english
	*\brief
	*	Command buffers queue.
	*/
	class Queue
	{
	protected:
		Queue( Device const & device
			, DeviceQueueCreateInfo info
			, uint32_t index );

	public:
		virtual ~Queue();
		/**
		*\~french
		*\brief
		*	Met des tampons de commandes dans la file.
		*\param[in] commandBuffers
		*	Les tampons de commandes.
		*\param[in] semaphoresToWait
		*	Les sémaphores à attendre lors de l'éxécution de la file.
		*\param[in] semaphoresStage
		*	Les étapes respectives des sémaphores.
		*\param[in] semaphoresToSignal
		*	Les sémaphores à signaler à la fin de l'éxécution de la file.
		*\param[in] fence
		*	Une barrière optionnelle.
		*\return
		*	\p true si tout s'est bien passé.
		*\~english
		*\brief
		*	Submits given command buffers.
		*\param[in] commandBuffers
		*	The command buffers.
		*\param[in] semaphoresToWait
		*	The semaphores to wait.
		*\param[in] semaphoresStage
		*	The semaphores respective stages.
		*\param[in] semaphoresToSignal
		*	The semaphores to signal.
		*\param[in] fence
		*	An optional fence.
		*\return
		*	\p true on ok.
		*/ 
		virtual void submit( CommandBufferCRefArray const & commandBuffers
			, SemaphoreCRefArray const & semaphoresToWait
			, PipelineStageFlagsArray const & semaphoresStage
			, SemaphoreCRefArray const & semaphoresToSignal
			, Fence const * fence )const = 0;
		/**
		*\~french
		*\brief
		*	Présente les swapchains données.
		*\param[in] swapChains
		*	Les swapchains.
		*\param[in] imagesIndex
		*	L'image à présenter pour chaque swapchain.
		*\param[in] semaphoresToWait
		*	Le sémaphores à attendre pour chaque swapchain.
		*\return
		*	Le résultat de la présentation de chaque swapchain.
		*\~english
		*\brief
		*	Presents the swapchains.
		*\param[in] swapChains
		*	The swapchains.
		*\param[in] imagesIndex
		*	The image to present for each swapchain.
		*\param[in] semaphoresToWait
		*	The semaphore to wait for each presented swapchain.
		*\return
		*	The result for each swapchain presentation.
		*/ 
		virtual ResultArray present( SwapChainCRefArray const & swapChains
			, UInt32Array const & imagesIndex
			, SemaphoreCRefArray const & semaphoresToWait )const = 0;
		/**
		*\~french
		*\brief
		*	Attend que la file soit inactive.
		*\return
		*	\p true si tout s'est bien passé.
		*\~english
		*\brief
		*	Waits for the queue to be idle.
		*\return
		*	\p true on ok.
		*/
		virtual void waitIdle()const = 0;
		/**
		*\~french
		*\brief
		*	Présente une swapchain.
		*\param[in] swapChain
		*	La swapchain.
		*\param[in] imageIndex
		*	L'image à présenter.
		*\param[in] semaphoreToWait
		*	Le sémaphore à attendre.
		*\return
		*	Le résultat de la présentation.
		*\~english
		*\brief
		*	Presents a swapchain.
		*\param[in] swapChain
		*	The swapchain.
		*\param[in] imageIndex
		*	The image to present.
		*\param[in] semaphoreToWait
		*	The semaphore to wait.
		*\return
		*	The presentation result.
		*/
		Result present( SwapChain const & swapChain
			, uint32_t imageIndex
			, Semaphore const & semaphoreToWait )const;
		/**
		*\~french
		*\return
		*	L'index de la famille de la file.
		*\~english
		*\return
		*	The queue family index.
		*/
		inline uint32_t getFamilyIndex()const
		{
			return m_createInfo.queueFamilyIndex;
		}
		/**
		*\~french
		*\return
		*	L'index de la file dans sa famille de file.
		*\~english
		*\return
		*	The queue index within its family.
		*/
		inline uint32_t getIndex()const
		{
			return m_index;
		}
		/**
		*\~french
		*\brief
		*	Met en attente des tampons de commandes.
		*\param[in] commandBuffer
		*	Le tampon de commandes.
		*\param[in] fence
		*	Une barrière optionnelle.
		*\return
		*	\p true si tout s'est bien passé.
		*\~english
		*\brief
		*	Submits given command buffer.
		*\param[in] commandBuffer
		*	The command buffer.
		*\param[in] fence
		*	An optional fence.
		*\return
		*	\p true on ok.
		*/
		inline void submit( CommandBuffer const & commandBuffer
			, Fence const * fence )const
		{
			submit( { commandBuffer }
				, SemaphoreCRefArray{}
				, PipelineStageFlagsArray{}
				, SemaphoreCRefArray{}
				, fence );
		}
		/**
		*\~french
		*\brief
		*	Met en attente un tampon de commandes.
		*\param[in] commandBuffer
		*	Le tampon de commandes.
		*\param[in] semaphoreToWait
		*	Le sémaphore à attendre lors de l'éxécution de la file.
		*\param[in] semaphoreStage
		*	L'étape du sémaphore.
		*\param[in] semaphoreToSignal
		*	Le sémaphore à signaler à la fin de l'éxécution de la file.
		*\param[in] fence
		*	Une barrière optionnelle.
		*\return
		*	\p true si tout s'est bien passé.
		*\~english
		*\brief
		*	Submits given command buffer.
		*\param[in] commandBuffer
		*	The command buffer.
		*\param[in] semaphoreToWait
		*	The semaphore to wait.
		*\param[in] semaphoreStage
		*	The semaphore respective stages.
		*\param[in] semaphoreToSignal
		*	The semaphore to signal.
		*\param[in] fence
		*	An optional fence.
		*\return
		*	\p true on ok.
		*/
		inline void submit( CommandBuffer const & commandBuffer
			, Semaphore const & semaphoreToWait
			, PipelineStageFlags const & semaphoreStage
			, Semaphore const & semaphoreToSignal
			, Fence const * fence )const
		{
			submit( { commandBuffer }
				, SemaphoreCRefArray{ semaphoreToWait }
				, PipelineStageFlagsArray{ semaphoreStage }
				, SemaphoreCRefArray{ semaphoreToSignal }
				, fence );
		}

	private:
		Device const & m_device;
		DeviceQueueCreateInfo m_createInfo;
		uint32_t m_index;
	};
}

#endif
