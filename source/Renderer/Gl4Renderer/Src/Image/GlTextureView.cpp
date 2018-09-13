#include "Image/GlTextureView.hpp"

#include "Core/GlDevice.hpp"
#include "Image/GlTexture.hpp"
#include "Sync/GlImageMemoryBarrier.hpp"

namespace gl_renderer
{
	namespace
	{
		GlTextureViewType convert( renderer::TextureViewType viewType
			, renderer::SampleCountFlag samples )
		{
			GlTextureViewType result = gl_renderer::convert( viewType );

			if ( samples > renderer::SampleCountFlag::e1 )
			{
				switch ( result )
				{
				case GL_TEXTURE_VIEW_2D:
					result = GL_TEXTURE_VIEW_2D_MULTISAMPLE;
					break;
				case GL_TEXTURE_VIEW_2D_ARRAY:
					result = GL_TEXTURE_VIEW_2D_MULTISAMPLE_ARRAY;
					break;
				default:
					assert( "Unsupported TextureViewType for a multisampled texture." );
					break;
				}
			}

			return result;
		}
	}

	TextureView::TextureView( Device const & device
		, Texture const & image )
		: renderer::TextureView{ device
		, image
		, {
			renderer::TextureViewType::e2D,
			image.getFormat(),
			renderer::ComponentMapping{},
			{
				renderer::ImageAspectFlag::eColour,
				0u,
				1u,
				0u,
				1u
			}
		} }
		, m_device{ device }
	{
	}

	TextureView::TextureView( Device const & device
		, Texture const & texture
		, renderer::ImageViewCreateInfo const & createInfo )
		: renderer::TextureView{ device
			, texture
			, createInfo }
		, m_device{ device }
		, m_target{ convert( m_createInfo.viewType, texture.getSamplesCount() ) }
	{
		auto context = m_device.getContext();
		glLogCall( context
			, glGenTextures
			, 1
			, &m_texture );
		glLogCall( context
			, glTextureView
			, m_texture
			, m_target
			, texture.getImage()
			, getInternal( m_createInfo.format )
			, m_createInfo.subresourceRange.baseMipLevel
			, m_createInfo.subresourceRange.levelCount
			, m_createInfo.subresourceRange.baseArrayLayer
			, m_createInfo.subresourceRange.layerCount );
		glLogCall( context
			, glBindTexture
			, m_target
			, m_texture );

		if ( m_createInfo.components.r != renderer::ComponentSwizzle::eIdentity )
		{
			glLogCall( context
				, glTexParameteri
				, m_target
				, GL_SWIZZLE_R
				, convert( m_createInfo.components.r ) );
		}

		if ( m_createInfo.components.g != renderer::ComponentSwizzle::eIdentity )
		{
			glLogCall( context
				, glTexParameteri
				, m_target
				, GL_SWIZZLE_G
				, convert( m_createInfo.components.g ) );
		}

		if ( m_createInfo.components.b != renderer::ComponentSwizzle::eIdentity )
		{
			glLogCall( context
				, glTexParameteri
				, m_target
				, GL_SWIZZLE_B
				, convert( m_createInfo.components.b ) );
		}

		if ( m_createInfo.components.a != renderer::ComponentSwizzle::eIdentity )
		{
			glLogCall( context
				, glTexParameteri
				, m_target
				, GL_SWIZZLE_A
				, convert( m_createInfo.components.a ) );
		}

		int minLevel = 0;
		context->glGetTexParameteriv( m_target, GL_TEXTURE_VIEW_MIN_LEVEL, &minLevel );
		assert( minLevel == m_createInfo.subresourceRange.baseMipLevel );
		int numLevels = 0;
		context->glGetTexParameteriv( m_target, GL_TEXTURE_VIEW_NUM_LEVELS, &numLevels );
		assert( numLevels == m_createInfo.subresourceRange.levelCount );
		int minLayer = 0;
		context->glGetTexParameteriv( m_target, GL_TEXTURE_VIEW_MIN_LAYER, &minLayer );
		assert( minLayer == m_createInfo.subresourceRange.baseArrayLayer );
		int numLayers = 0;
		context->glGetTexParameteriv( m_target, GL_TEXTURE_VIEW_NUM_LAYERS, &numLayers );
		assert( numLayers == m_createInfo.subresourceRange.layerCount );
		glLogCall( context
			, glBindTexture
			, m_target
			, 0u );
	}

	TextureView::~TextureView()
	{
		auto context = m_device.getContext();
		glLogCall( context
			, glDeleteTextures
			, 1
			, &m_texture );
	}

	GLuint TextureView::getImage()const noexcept
	{
		assert( m_texture != GL_INVALID_INDEX );
		return m_texture;
	}
}