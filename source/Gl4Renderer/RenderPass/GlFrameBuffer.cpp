/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "RenderPass/GlFrameBuffer.hpp"

#include "Command/GlQueue.hpp"
#include "Core/GlDevice.hpp"
#include "RenderPass/GlRenderPass.hpp"
#include "Image/GlImage.hpp"
#include "Image/GlImageView.hpp"

#include <Ashes/RenderPass/AttachmentReference.hpp>

#include <iostream>

namespace gl_renderer
{
	namespace
	{
		enum GlFramebufferStatus
			: GLenum
		{
			GL_FRAMEBUFFER_STATUS_UNDEFINED = 0x8219,
			GL_FRAMEBUFFER_STATUS_COMPLETE = 0x8CD5,
			GL_FRAMEBUFFER_STATUS_INCOMPLETE_ATTACHMENT = 0x8CD6,
			GL_FRAMEBUFFER_STATUS_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7,
			GL_FRAMEBUFFER_STATUS_INCOMPLETE_DRAW_BUFFER = 0x8CDB,
			GL_FRAMEBUFFER_STATUS_INCOMPLETE_READ_BUFFER = 0x8CDC,
			GL_FRAMEBUFFER_STATUS_UNSUPPORTED = 0x8CDD,
			GL_FRAMEBUFFER_STATUS_INCOMPLETE_MULTISAMPLE = 0x8D56,
			GL_FRAMEBUFFER_STATUS_INCOMPLETE_LAYER_TARGETS = 0x8DA8,
		};

		bool isSRGBFormat( ashes::Format format )
		{
			return format == ashes::Format::eR8G8_SRGB
				|| format == ashes::Format::eR8G8B8_SRGB
				|| format == ashes::Format::eB8G8R8_SRGB
				|| format == ashes::Format::eR8G8B8A8_SRGB
				|| format == ashes::Format::eB8G8R8A8_SRGB
				|| format == ashes::Format::eA8B8G8R8_SRGB_PACK32;
		}

		GlAttachmentPoint getAttachmentPoint( ashes::Format format )
		{
			if ( ashes::isDepthStencilFormat( format ) )
			{
				return GL_ATTACHMENT_POINT_DEPTH_STENCIL;
			}

			if ( ashes::isStencilFormat( format ) )
			{
				return GL_ATTACHMENT_POINT_STENCIL;
			}

			if ( ashes::isDepthFormat( format ) )
			{
				return GL_ATTACHMENT_POINT_DEPTH;
			}

			return GL_ATTACHMENT_POINT_COLOR0;
		}

		GlAttachmentPoint getAttachmentPoint( ImageView const & texture )
		{
			return getAttachmentPoint( texture.getFormat() );
		}

		GlAttachmentType getAttachmentType( ashes::Format format )
		{
			if ( ashes::isDepthStencilFormat( format ) )
			{
				return GL_ATTACHMENT_TYPE_DEPTH_STENCIL;
			}

			if ( ashes::isStencilFormat( format ) )
			{
				return GL_ATTACHMENT_TYPE_STENCIL;
			}

			if ( ashes::isDepthFormat( format ) )
			{
				return GL_ATTACHMENT_TYPE_DEPTH;
			}

			return GL_ATTACHMENT_TYPE_COLOR;
		}

		GlAttachmentType getAttachmentType( ImageView const & texture )
		{
			return getAttachmentType( texture.getFormat() );
		}
	}

	void checkCompleteness( GLenum status )
	{
		switch ( status )
		{
		case 0:
			ashes::Logger::logError( "An error has occured." );
			assert( false );
			break;

		case GL_FRAMEBUFFER_STATUS_COMPLETE:
			break;

		case GL_FRAMEBUFFER_STATUS_UNDEFINED:
			ashes::Logger::logError( "The specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist." );
			assert( false );
			break;

		case GL_FRAMEBUFFER_STATUS_INCOMPLETE_ATTACHMENT:
			ashes::Logger::logError( "At least one of the framebuffer attachment points are framebuffer incomplete." );
			assert( false );
			break;

		case GL_FRAMEBUFFER_STATUS_INCOMPLETE_MISSING_ATTACHMENT:
			ashes::Logger::logError( "The framebuffer does not have at least one image attached to it." );
			assert( false );
			break;

		case GL_FRAMEBUFFER_STATUS_INCOMPLETE_DRAW_BUFFER:
			ashes::Logger::logError( "The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi." );
			assert( false );
			break;

		case GL_FRAMEBUFFER_STATUS_INCOMPLETE_READ_BUFFER:
			ashes::Logger::logError( "GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER." );
			assert( false );
			break;

		case GL_FRAMEBUFFER_STATUS_UNSUPPORTED:
			ashes::Logger::logError( "The combination of internal formats of the attached images violates an implementation-dependent set of restrictions." );
			assert( false );
			break;

		case GL_FRAMEBUFFER_STATUS_INCOMPLETE_MULTISAMPLE:
			ashes::Logger::logError( "One of the following:" );
			ashes::Logger::logError( "  - The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers;" );
			ashes::Logger::logError( "  - The value of GL_TEXTURE_SAMPLES is the not same for all attached textures;" );
			ashes::Logger::logError( "  - The attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES;" );
			ashes::Logger::logError( "  - The value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures;" );
			ashes::Logger::logError( "  - The attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures." );
			assert( false );
			break;

		case GL_FRAMEBUFFER_STATUS_INCOMPLETE_LAYER_TARGETS:
			ashes::Logger::logError( "At least one framebuffer attachment is layered, and any populated attachment is not layered, or all populated color attachments are not from textures of the same target." );
			assert( false );
			break;
		}
	}

	FrameBuffer::FrameBuffer( Device const & device
		, RenderPass const & renderPass
		, ashes::Extent2D const & dimensions
		, ashes::FrameBufferAttachmentArray views )
		: ashes::FrameBuffer{ renderPass, dimensions, std::move( views ) }
		, m_device{ device }
		, m_frameBuffer{ 0u }
		, m_renderPass{ renderPass }
	{
		doInitialiseFramebuffer();
	}

	FrameBuffer::~FrameBuffer()
	{
		if ( m_frameBuffer > 0u )
		{
			auto context = m_device.getContext();
			glLogCall( context
				, glDeleteFramebuffers
				, 1
				, &m_frameBuffer );
		}
	}

	void FrameBuffer::setDrawBuffers( ContextLock const & context
		, AttachmentDescriptionArray const & attaches )const
	{
		m_drawBuffers.clear();

		for ( auto & attach : attaches )
		{
			auto & fboAttach = m_attachments[attach.index];

			if ( static_cast< Image const & >( fboAttach.getImage() ).hasImage() )
			{
				m_drawBuffers.push_back( getAttachmentPoint( attach.attach.get().format ) + attach.index );
			}
			else if ( attaches.size() == 1 )
			{
				m_drawBuffers.push_back( GL_ATTACHMENT_POINT_BACK );
			}
		}

		glLogCall( context
			, glDrawBuffers
			, GLsizei( m_drawBuffers.size() )
			, m_drawBuffers.data() );
	}

	void FrameBuffer::setDrawBuffers( ContextLock const & context
		, ashes::AttachmentReferenceArray const & attaches )const
	{
		if ( getInternal() != GL_INVALID_INDEX )
		{
			ashes::UInt32Array colours;

			if ( m_colourAttaches.empty() && attaches.size() == 1 )
			{
				colours.push_back( GL_ATTACHMENT_POINT_BACK );
			}
			else
			{
				for ( auto & attach : attaches )
				{
					auto & fboAttach = m_colourAttaches[attach.attachment];
					colours.push_back( fboAttach.point + attach.attachment );
				}
			}

			if ( m_drawBuffers != colours )
			{
				m_drawBuffers = colours;
				glLogCall( context
					, glDrawBuffers
					, GLsizei( m_drawBuffers.size() )
					, m_drawBuffers.data() );
			}
		}
	}

	void FrameBuffer::doInitialiseFramebuffer()
	{
		auto context = m_device.getContext();
		glLogCall( context
			, glGenFramebuffers
			, 1
			, &m_frameBuffer );
		glLogCall( context
			, glBindFramebuffer
			, GL_FRAMEBUFFER
			, m_frameBuffer );

		for ( auto & attach : m_attachments )
		{
			auto & glview = static_cast< ImageView const & >( attach.getView() );
			auto & gltexture = static_cast< Image const & >( glview.getImage() );
			assert( gltexture.hasImage() );
			doInitialiseFboAttach( attach );
		}

		checkCompleteness( context->glCheckFramebufferStatus( GL_FRAMEBUFFER ) );
		glLogCall( context
			, glBindFramebuffer
			, GL_FRAMEBUFFER
			, 0 );
	}

	void FrameBuffer::doInitialiseFboAttach( ashes::FrameBufferAttachment const & attach )
	{
		auto context = m_device.getContext();
		auto & glview = static_cast< ImageView const & >( attach.getView() );
		auto & gltexture = static_cast< Image const & >( glview.getImage() );
		uint32_t index = m_renderPass.getAttachmentIndex( attach.getAttachment() );
		auto image = glview.getInternal();
		auto mipLevel = glview.getSubResourceRange().baseMipLevel;

		if ( glview.getSubResourceRange().baseMipLevel )
		{
			if ( gltexture.getLayerCount() == 1u )
			{
				image = gltexture.getInternal();
			}
			else
			{
				mipLevel = 0u;
			}
		}

		Attachment attachment
		{
			getAttachmentPoint( glview ),
			image,
			getAttachmentType( glview ),
		};

		if ( attachment.point == GL_ATTACHMENT_POINT_DEPTH_STENCIL
			|| attachment.point == GL_ATTACHMENT_POINT_DEPTH
			|| attachment.point == GL_ATTACHMENT_POINT_STENCIL )
		{
			m_depthStencilAttach = attachment;
		}
		else
		{
			m_colourAttaches.push_back( attachment );
			m_srgb |= isSRGBFormat( glview.getFormat() );
		}

		m_allAttaches.push_back( attachment );
		auto target = GL_TEXTURE_2D;

		if ( gltexture.getSamplesCount() > ashes::SampleCountFlag::e1 )
		{
			target = GL_TEXTURE_2D_MULTISAMPLE;
		}

		glLogCall( context
			, glFramebufferTexture2D
			, GL_FRAMEBUFFER
			, GlAttachmentPoint( attachment.point + index )
			, target
			, attachment.object
			, mipLevel );
		checkCompleteness( context->glCheckFramebufferStatus( GL_FRAMEBUFFER ) );
	}
}
