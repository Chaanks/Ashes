/**
*\file
*	Image.h
*\author
*	Sylvain Doremus
*/
#ifndef ___GlRenderer_Texture_HPP___
#define ___GlRenderer_Texture_HPP___
#pragma once

#include "Gl4Renderer/GlRendererPrerequisites.hpp"

#include <Ashes/Image/Image.hpp>

namespace gl_renderer
{
	/**
	*\brief
	*	Une texture, avec son image et son échantillonneur.
	*/
	class Image
		: public ashes::Image
	{
	public:
		/**
		*\brief
		*	Constructeur.
		*\remarks
		*	Used for swapchain own image.
		*\param[in] device
		*	Le périphérique logique.
		*/
		Image( Device const & device
			, ashes::Format format
			, ashes::Extent2D const & dimensions );
		/**
		*\brief
		*	Constructeur.
		*\remarks
		*	Used for swapchain images creation.
		*\param[in] device
		*	Le périphérique logique.
		*/
		Image( Device const & device
			, Image const & image );
		/**
		*\brief
		*	Constructeur.
		*\param[in] device
		*	Le périphérique logique.
		*/
		Image( Device const & device
			, ashes::ImageCreateInfo const & createInfo );
		/**
		*\brief
		*	Destructeur.
		*/
		~Image();
		/**
		*\copydoc	ashes::Image::getMemoryRequirements
		*/
		ashes::MemoryRequirements getMemoryRequirements()const override;
		/**
		*\copydoc	ashes::Image::getMemoryRequirements
		*/
		void generateMipmaps( ashes::CommandBuffer & commandBuffer )const override;
		/**
		*\copydoc	ashes::Image::createView
		*/
		ashes::ImageViewPtr createView( ashes::ImageViewCreateInfo const & createInfo )const override;

		inline bool hasImage()const noexcept
		{
			return m_texture != GL_INVALID_INDEX;
		}
		/**
		*\return
		*	L'image OpenGL.
		*/
		inline bool hasInternal()const noexcept
		{
			return m_texture != GL_INVALID_INDEX;
		}
		/**
		*\return
		*	L'image OpenGL.
		*/
		inline GLuint getInternal()const noexcept
		{
			assert( hasInternal() );
			return m_texture;
		}
		/**
		*\return
		*	Le nombre d'échantillons.
		*/
		inline ashes::SampleCountFlag getSamplesCount()const noexcept
		{
			return m_createInfo.samples;
		}

	private:
		void doBindMemory()override;

	private:
		Device const & m_device;
		GlTextureType m_target;
		GLuint m_texture{ GL_INVALID_INDEX };
		bool m_ownTexture{ true };
	};
}

#endif
