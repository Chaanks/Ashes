/*
This file belongs to GlInstance.
See LICENSE file in root folder.
*/
#include "Command/Commands/GlCopyImageToBufferCommand.hpp"

#include "Buffer/GlBuffer.hpp"
#include "Core/GlDevice.hpp"
#include "Image/GlImage.hpp"
#include "Image/GlImageView.hpp"

#include <Ashes/Image/ImageSubresourceRange.hpp>
#include <Ashes/Miscellaneous/BufferImageCopy.hpp>

namespace gl_renderer
{
	namespace
	{
		std::vector< ImageViewPtr > createViews( Device const & device
			, ashes::Image const & texture
			, ashes::BufferImageCopyArray const & copies )
		{
			std::vector< ImageViewPtr > result;
			ashes::ImageType type = texture.getType();
			ashes::ImageViewType viewType;

			if ( type == ashes::ImageType::e3D )
			{
				viewType = ashes::ImageViewType::e3D;
			}
			else if ( type == ashes::ImageType::e2D )
			{
				viewType = ashes::ImageViewType::e2D;
			}
			else if ( type == ashes::ImageType::e1D )
			{
				viewType = ashes::ImageViewType::e1D;
			}

			for ( auto & copy : copies )
			{
				ashes::ImageViewCreateInfo createInfo{};
				createInfo.viewType = viewType;
				createInfo.format = texture.getFormat();
				createInfo.subresourceRange.aspectMask = ashes::getAspectMask( createInfo.format );
				createInfo.subresourceRange.baseArrayLayer = copy.imageSubresource.baseArrayLayer;
				createInfo.subresourceRange.layerCount = copy.imageSubresource.layerCount;
				createInfo.subresourceRange.baseMipLevel = copy.imageSubresource.mipLevel;
				createInfo.subresourceRange.levelCount = 1u;
				result.emplace_back( std::make_unique< ImageView >( device
					, static_cast< Image const & >( texture )
					, createInfo ) );
			}

			return result;
		}
	}

	CopyImageToBufferCommand::CopyImageToBufferCommand( Device const & device
		, ashes::BufferImageCopyArray const & copyInfo
		, ashes::Image const & src
		, ashes::BufferBase const & dst )
		: CommandBase{ device }
		, m_src{ static_cast< Image const & >( src ) }
		, m_dst{ static_cast< Buffer const & >( dst ) }
		, m_copyInfo{ copyInfo }
		, m_internal{ getInternalFormat( m_src.getFormat() ) }
		, m_format{ getFormat( m_internal ) }
		, m_type{ getType( m_internal ) }
		, m_target{ convert( m_src.getType(), 1u ) }
		, m_views{ createViews( m_device, m_src, m_copyInfo ) }
		, m_srcFbo{ device.getBlitSrcFbo() }
	{
	}

	CopyImageToBufferCommand::CopyImageToBufferCommand( CopyImageToBufferCommand const & rhs )
		: CommandBase{ rhs.m_device }
		, m_src{ rhs.m_src }
		, m_dst{ rhs.m_dst }
		, m_copyInfo{ rhs.m_copyInfo }
		, m_internal{ rhs.m_internal }
		, m_format{ rhs.m_format }
		, m_type{ rhs.m_type }
		, m_target{ rhs.m_target }
		, m_views{ createViews( m_device, m_src, m_copyInfo ) }
		, m_srcFbo{ rhs.m_srcFbo }
	{
	}

	void CopyImageToBufferCommand::apply( ContextLock const & context )const
	{
		glLogCommand( "CopyImageToBufferCommand" );
		glLogCall( context
			, glBindBuffer
			, GL_BUFFER_TARGET_PIXEL_PACK
			, m_dst.getInternal() );

		for ( size_t i = 0; i < m_views.size(); ++i )
		{
			applyOne( context
				, m_copyInfo[i]
				, *m_views[i] );
		}

		glLogCall( context
			, glBindBuffer
			, GL_BUFFER_TARGET_PIXEL_PACK
			, 0u );
	}

	void CopyImageToBufferCommand::applyOne( ContextLock const & context
		, ashes::BufferImageCopy const & copyInfo
		, ImageView const & view )const
	{
		// Setup source FBO
		glLogCall( context
			, glBindFramebuffer
			, GL_FRAMEBUFFER
			, m_srcFbo );
		glLogCall( context
			, glFramebufferTexture2D
			, GL_FRAMEBUFFER
			, GL_ATTACHMENT_POINT_COLOR0
			, GL_TEXTURE_2D
			, view.getInternal()
			, 0u );
		glLogCall( context
			, glReadBuffer
			, GL_ATTACHMENT_POINT_COLOR0 );
		glLogCall( context
			, glBindFramebuffer
			, GL_FRAMEBUFFER
			, m_device.getCurrentFramebuffer() );

		// Read pixels
		glLogCall( context
			, glBindFramebuffer
			, GL_READ_FRAMEBUFFER
			, m_srcFbo );
		glLogCall( context
			, glReadPixels
			, copyInfo.imageOffset.x
			, copyInfo.imageOffset.y
			, copyInfo.imageExtent.width
			, copyInfo.imageExtent.height
			, m_format
			, m_type
			, nullptr );
		glLogCall( context
			, glBindFramebuffer
			, GL_READ_FRAMEBUFFER
			, 0u );
	}

	CommandPtr CopyImageToBufferCommand::clone()const
	{
		return std::make_unique< CopyImageToBufferCommand >( *this );
	}
}
