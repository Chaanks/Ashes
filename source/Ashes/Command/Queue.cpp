/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "Ashes/Command/Queue.hpp"

#include "Ashes/Core/Device.hpp"

namespace ashes
{
	Queue::Queue( Device const & device
		, DeviceQueueCreateInfo createInfo
		, uint32_t index )
		: m_device{ device }
		, m_createInfo{ std::move( createInfo ) }
		, m_index{ index }
	{
		registerObject( m_device, "Queue", this );
	}

	Queue::~Queue()
	{
		unregisterObject( m_device, this );
	}

	Result Queue::present( SwapChain const & swapChain
		, uint32_t imageIndex
		, Semaphore const & semaphoreToWait )const
	{
		return present( { std::ref( swapChain ) }
			, { imageIndex }
			, { std::ref( semaphoreToWait ) } ).front();
	}
}
