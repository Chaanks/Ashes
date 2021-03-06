/**
*\file
*	Image.h
*\author
*	Sylvain Doremus
*/
#ifndef ___VkRenderer_Texture_HPP___
#define ___VkRenderer_Texture_HPP___
#pragma once

#include "VkRenderer/VkRendererPrerequisites.hpp"

#include <Ashes/Image/Image.hpp>

namespace vk_renderer
{
	/**
	*\~french
	*\brief
	*	Classe encapsulant le concept d'image Vulkan.
	*\remarks
	*	Gère la transition de layouts.
	*	Dépendant du fait que l'image provienne de la swap chain
	*	ou d'une ressource, la VkImage sera détruite par le parent
	*	correspondant.
	*\~english
	*\brief
	*	Class wrapping the Vulkan image concept.
	*\remarks
	*	Handles the layouts transition.
	*	Depending on wheter the image comes from a resource or a swap chain,
	*	The VkImage will be destroyed or not.
	*/
	class Image
		: public ashes::Image
	{
	public:
		Image( Image const & ) = delete;
		Image & operator=( Image const & ) = delete;
		Image( Image && rhs );
		Image & operator=( Image && rhs );
		/**
		*\brief
		*	Constructeur.
		*/
		Image( Device const & device
			, ashes::ImageCreateInfo const & createInfo );
		/**
		*\brief
		*	Constructeur.
		*\param[in] device
		*	Le périphérique logique.
		*/
		Image( Device const & device
			, ashes::Format format
			, ashes::Extent2D const & dimensions
			, VkImage image );
		/**
		*\brief
		*	Constructeur.
		*\param[in] device
		*	Le périphérique logique.
		*/
		Image( Device const & device
			, ashes::Format format
			, ashes::Extent2D const & dimensions
			, ashes::ImageUsageFlags usageFlags
			, ashes::ImageTiling tiling
			, ashes::MemoryPropertyFlags memoryFlags );
		/**
		*\brief
		*	Destructeur.
		*/
		~Image();
		/**
		*\copydoc	ashes::Image::createView
		*/
		ashes::MemoryRequirements getMemoryRequirements()const override;
		/**
		*\copydoc	ashes::Image::createView
		*/
		ashes::ImageViewPtr createView( ashes::ImageViewCreateInfo const & createInfo )const override;
		/**
		*\~french
		*\brief
		*	Opérateur de conversion implicite vers VkImage.
		*\~english
		*\brief
		*	VkImage implicit cast operator.
		*/
		inline operator VkImage const &( )const
		{
			return m_image;
		}

	private:
		void doBindMemory()override;

	private:
		Device const & m_device;
		VkImage m_image{};
		VkImageCreateInfo m_vkCreateInfo;
		bool m_owner{};
	};
}

#endif
