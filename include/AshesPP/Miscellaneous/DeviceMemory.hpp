/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___AshesPP_DeviceMemory_HPP___
#define ___AshesPP_DeviceMemory_HPP___
#pragma once

#include "AshesPP/AshesPPPrerequisites.hpp"

#include "AshesPP/Core/Device.hpp"

namespace ashespp
{
	/**
	*\~english
	*\brief
	*	Computes an aligned size.
	*\param[in] size
	*	The unaligned size.
	*\param[in] align
	*	The alignment value.
	*\return
	*	The aligned size.
	*\~french
	*\brief
	*	Calcule une taille alignée.
	*\param[in] size
	*	La taille non alignée.
	*\param[in] align
	*	La valeur d'alignement.
	*\return
	*	La taille alignée.
	*/
	inline VkDeviceSize getAlignedSize( VkDeviceSize size, VkDeviceSize align )
	{
		VkDeviceSize result = 0u;

		while ( size > align )
		{
			size -= align;
			result += align;
		}

		return result + align;
	}
	/**
	*\~english
	*\brief
	*	A device memory object.
	*\~french
	*\brief
	*	Un objet mémoire.
	*/
	class DeviceMemory
	{
	public:
		DeviceMemory( Device const & device
			, VkMemoryAllocateInfo allocateInfo );
		~DeviceMemory();
		/**
		*\~english
		*\brief
		*	Maps a range of the memory in RAM.
		*\param[in] offset
		*	The range beginning offset.
		*\param[in] size
		*	The range size.
		*\param[in] flags
		*	The mapping flags.
		*\return
		*	\p nullptr if mapping failed.
		*\~french
		*\brief
		*	Mappe la mémoire en RAM.
		*\param[in] offset
		*	L'offset à partir duquel la mémoire est mappée.
		*\param[in] size
		*	La taille en octets de la mémoire à mapper.
		*\param[in] flags
		*	Indicateurs de configuration du mapping.
		*\return
		*	\p nullptr si le mapping a échoué.
		*/
		uint8_t * lock( VkDeviceSize offset
			, VkDeviceSize size
			, VkMemoryMapFlags flags )const;
		/**
		*\~english
		*\brief
		*	Invalidates the memory content.
		*\param[in] offset
		*	The mapped memory starting offset.
		*\param[in] size
		*	The range size.
		*\~french
		*\brief
		*	Invalide le contenu de la mémoire.
		*\param[in] offset
		*	L'offset de la mémoire mappée.
		*\param[in] size
		*	La taille en octets de la mémoire mappée.
		*/
		void invalidate( VkDeviceSize offset
			, VkDeviceSize size )const;
		/**
		*\~english
		*\brief
		*	Updates the VRAM.
		*\param[in] offset
		*	The mapped memory starting offset.
		*\param[in] size
		*	The range size.
		*\~french
		*\brief
		*	Met à jour la VRAM.
		*\param[in] offset
		*	L'offset de la mémoire mappée.
		*\param[in] size
		*	La taille en octets de la mémoire mappée.
		*/
		void flush( VkDeviceSize offset
			, VkDeviceSize size )const;
		/**
		*\~english
		*\brief
		*	Unmaps the memory from RAM.
		*\~french
		*\brief
		*	Unmappe la mémoire de la RAM.
		*/
		void unlock()const;
		/**
		*\~french
		*\brief
		*	Conversion implicite vers VkDeviceMemory.
		*\~english
		*\brief
		*	VkDeviceMemory implicit cast operator.
		*/
		inline operator VkDeviceMemory const & ()const
		{
			return m_internal;
		}

	protected:
		Device const & m_device;
		VkMemoryAllocateInfo m_allocateInfo;
		VkDeviceMemory m_internal{ VK_NULL_HANDLE };
	};
}

#endif