/*
This file belongs to Ashes.
See LICENSE file in root folder
*/
#pragma once

#include "D3D11Renderer/Command/Commands/D3D11CommandBase.hpp"

namespace ashes::d3d11
{
	class WaitEventsCommand
		: public CommandBase
	{
	public:
		WaitEventsCommand( Device const & device
			, ashes::EventCRefArray const & events
			, ashes::PipelineStageFlags srcStageMask
			, ashes::PipelineStageFlags dstStageMask
			, ashes::BufferMemoryBarrierArray const & bufferMemoryBarriers
			, ashes::VkImageMemoryBarrierArray const & imageMemoryBarriers );
		void apply( Context const & context )const;
		CommandPtr clone()const;

	private:
		ashes::EventCRefArray const & m_events;
	};
}
