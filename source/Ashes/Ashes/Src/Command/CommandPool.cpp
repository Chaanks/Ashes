/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "Command/CommandPool.hpp"

#include "Command/CommandBuffer.hpp"
#include "Core/Device.hpp"

namespace ashes
{
	CommandPool::CommandPool( Device const & device
		, uint32_t queueFamilyIndex
		, CommandPoolCreateFlags flags )
		: m_device{ device }
	{
		registerObject( m_device, "CommandPool", this );
	}

	CommandPool::~CommandPool()
	{
		unregisterObject( m_device, this );
	}
}