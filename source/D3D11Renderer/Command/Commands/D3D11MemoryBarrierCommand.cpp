/*
This file belongs to GlInstance.
See LICENSE file in root folder.
*/
#include "Command/Commands/D3D11MemoryBarrierCommand.hpp"

namespace ashes::d3d11
{
	MemoryBarrierCommand::MemoryBarrierCommand( Device const & device
		, ashes::PipelineStageFlags after
		, ashes::PipelineStageFlags before
		, ashes::MemoryBarrierArray const & memoryBarriers
		, ashes::BufferMemoryBarrierArray const & bufferBarriers
		, ashes::VkImageMemoryBarrierArray const & imageBarriers )
		: CommandBase{ device }
	{
	}

	void MemoryBarrierCommand::apply( Context const & context )const
	{
	}

	CommandPtr MemoryBarrierCommand::clone()const
	{
		return std::make_unique< MemoryBarrierCommand >( *this );
	}
}
