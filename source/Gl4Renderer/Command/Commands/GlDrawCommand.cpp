/*
This file belongs to GlInstance.
See LICENSE file in root folder.
*/
#include "Command/Commands/GlDrawCommand.hpp"

namespace gl_renderer
{
	DrawCommand::DrawCommand( Device const & device
		, uint32_t vtxCount
		, uint32_t instCount
		, uint32_t firstVertex
		, uint32_t firstInstance
		, ashes::PrimitiveTopology mode )
		: CommandBase{ device }
		, m_vtxCount{ vtxCount }
		, m_instCount{ instCount }
		, m_firstVertex{ firstVertex }
		, m_firstInstance{ firstInstance }
		, m_mode{ convert( mode ) }
	{
	}

	void DrawCommand::apply( ContextLock const & context )const
	{
		assert( m_instCount >= 1 );
		glLogCommand( "DrawCommand" );
		glLogCall( context
			, glDrawArraysInstancedBaseInstance
			, m_mode
			, m_firstVertex
			, m_vtxCount
			, m_instCount
			, m_firstInstance );
	}

	CommandPtr DrawCommand::clone()const
	{
		return std::make_unique< DrawCommand >( *this );
	}
}
