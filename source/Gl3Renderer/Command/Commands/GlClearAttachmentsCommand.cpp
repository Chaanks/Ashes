/*
This file belongs to GlInstance.
See LICENSE file in root folder.
*/
#include "Command/Commands/GlClearAttachmentsCommand.hpp"

#include "Core/GlDevice.hpp"
#include "Image/GlImageView.hpp"

namespace gl_renderer
{
	namespace
	{
		void doClear( ContextLock const & context
			, ashes::ClearAttachment const & clearAttach )
		{
			if ( ashes::checkFlag( clearAttach.aspectMask, ashes::ImageAspectFlag::eColour ) )
			{
				assert( clearAttach.clearValue.isColour() );
				auto & colour = clearAttach.clearValue.colour();
				glLogCall( context
					, glClearBufferfv
					, GL_CLEAR_TARGET_COLOR
					, clearAttach.colourAttachment
					, colour.float32.data() );
			}
			else
			{
				assert( !clearAttach.clearValue.isColour() );
				auto & depthStencil = clearAttach.clearValue.depthStencil();
				auto stencil = GLint( depthStencil.stencil );

				if ( ashes::checkFlag( clearAttach.aspectMask, ashes::ImageAspectFlag::eDepth | ashes::ImageAspectFlag::eStencil ) )
				{
					glLogCall( context
						, glClearBufferfi
						, GL_CLEAR_TARGET_DEPTH_STENCIL
						, 0u
						, depthStencil.depth
						, stencil );
				}
				else if ( ashes::checkFlag( clearAttach.aspectMask, ashes::ImageAspectFlag::eDepth ) )
				{
					glLogCall( context
						, glClearBufferfv
						, GL_CLEAR_TARGET_DEPTH
						, 0u
						, &depthStencil.depth );
				}
				else if ( ashes::checkFlag( clearAttach.aspectMask, ashes::ImageAspectFlag::eStencil ) )
				{
					glLogCall( context
						, glClearBufferiv
						, GL_CLEAR_TARGET_STENCIL
						, 0u
						, &stencil );
				}
			}
		}

	}

	ClearAttachmentsCommand::ClearAttachmentsCommand( Device const & device
		, ashes::ClearAttachmentArray const & clearAttaches
		, ashes::ClearRectArray const & clearRects )
		: CommandBase{ device }
		, m_clearAttaches{ clearAttaches }
		, m_clearRects{ clearRects }
	{
	}

	void ClearAttachmentsCommand::apply( ContextLock const & context )const
	{
		glLogCommand( "ClearAttachmentsCommand" );
		auto scissor = m_device.getCurrentScissor();

		for ( auto & clearAttach : m_clearAttaches )
		{
			for ( auto & rect : m_clearRects )
			{
				glLogCall( context
					, glScissor
					, rect.offset.x
					, rect.offset.x
					, rect.extent.width
					, rect.extent.height );
				doClear( context, clearAttach );
			}
		}

		glLogCall( context
			, glScissor
			, scissor.offset.x
			, scissor.offset.y
			, scissor.size.width
			, scissor.size.height );
	}

	CommandPtr ClearAttachmentsCommand::clone()const
	{
		return std::make_unique< ClearAttachmentsCommand >( *this );
	}
}
