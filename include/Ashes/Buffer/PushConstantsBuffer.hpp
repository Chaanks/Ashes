/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___Ashes_PushConstantsBuffer_HPP___
#define ___Ashes_PushConstantsBuffer_HPP___
#pragma once

#include "Ashes/Core/Device.hpp"

namespace ashes
{
	/**
	*\~english
	*\brief
	*	A variable for a push constants buffer.
	*\~french
	*\brief
	*	Une variable pour un tampon de push constants.
	*/
	struct PushConstant
	{
		/**
		*\~english
		*\brief
		*	The offset in the buffer.
		*\~french
		*\brief
		*	Le décalage dans le tampon.
		*/
		uint32_t offset;
		/**
		*\~english
		*\brief
		*	The variable format, the size of the variable is deduced from that.
		*\~french
		*\brief
		*	Le format de la variable, la taille de la variable est déduite de là.
		*/
		ConstantFormat format;
		/**
		*\~english
		*\brief
		*	The dimensions of the array, if the constant is an array.
		*\~french
		*\brief
		*	Les dimensions du tableau, si la constante est un tableau.
		*/
		uint32_t arraySize{ 1u };
	};
	/**
	*\~english
	*\brief
	*	Wraps the push constants concept.
	*\~french
	*\brief
	*	Wrappe le concept de push constants.
	*/
	class PushConstantsBufferBase
	{
	public:
		/**
		*\~french
		*\brief
		*	Constructeur.
		*\param[in] stageFlags
		*	Spécifie les niveaux de shaders qui vont utiliser les push constants dans l'intervalle mis à jour.
		*\param[in] variables
		*	Les variables contenues dans le tampon.
		*\~english
		*\brief
		*	Constructor.
		*\param[in] stageFlags
		*	Specifies the shader stages that will use the push constants in the updated range.
		*\param[in] variables
		*	The constants contained in the buffer.
		*/
		PushConstantsBufferBase( ShaderStageFlags stageFlags
			, PushConstantArray const & variables );
		/**
		*\~french
		*\brief
		*	Destructeur.
		*\~english
		*\brief
		*	Destructor.
		*/
		~PushConstantsBufferBase()
		{
		}
		/**
		*\~english
		*\return
		*	The base offset.
		*\~french
		*\return
		*	Le décalage de base.
		*/
		inline uint32_t getOffset()const
		{
			return m_offset;
		}
		/**
		*\~english
		*\return
		*	The data size.
		*\~french
		*\return
		*	La taille des données.
		*/
		inline uint32_t getSize()const
		{
			return uint32_t( m_data.size() );
		}
		/**
		*\~english
		*\return
		*	The shader stages that will use the push constants in the updated range.
		*\~french
		*\return
		*	Les niveaux de shaders qui vont utiliser les push constants dans l'intervalle mis à jour.
		*/
		inline ShaderStageFlags getStageFlags()const
		{
			return m_stageFlags;
		}
		/**
		*\~english
		*\brief
		*	A pointer to the buffer data.
		*\~french
		*\brief
		*	Un pointeur sur les données du tampon.
		*/
		inline uint8_t const * getData()const
		{
			return m_data.data();
		}
		/**
		*\~english
		*\brief
		*	A pointer to the buffer data.
		*\~french
		*\brief
		*	Un pointeur sur les données du tampon.
		*/
		inline uint8_t * getData()
		{
			return m_data.data();
		}
		/**
		*\~english
		*\return
		*	The beginning of the constants array.
		*\~french
		*\return
		*	Le début du tableau de constantes.
		*/
		inline PushConstantArray::const_iterator begin()const
		{
			return m_variables.begin();
		}
		/**
		*\~english
		*\return
		*	The end of the constants array.
		*\~french
		*\return
		*	La fin du tableau de constantes.
		*/
		inline PushConstantArray::const_iterator end()const
		{
			return m_variables.end();
		}

	protected:
		ShaderStageFlags m_stageFlags;
		PushConstantArray m_variables;
		uint32_t m_offset;
		ashes::ByteArray m_data;
	};
	/**
	*\~english
	*\brief
	*	Template class wrapping a PushConstantsBufferBase.
	*\~french
	*\brief
	*	Classe template wrappant un PushConstantsBufferBase.
	*/
	template< typename T >
	class PushConstantsBuffer
	{
	public:
		/**
		*\~french
		*\brief
		*	Constructeur.
		*\param[in] stageFlags
		*	Spécifie les niveaux de shaders qui vont utiliser les push constants dans l'intervalle mis à jour.
		*\param[in] variables
		*	Les variables contenues dans le tampon.
		*\~english
		*\brief
		*	Constructor.
		*\param[in] stageFlags
		*	Specifies the shader stages that will use the push constants in the updated range.
		*\param[in] variables
		*	The constants contained in the buffer.
		*/
		PushConstantsBuffer( ShaderStageFlags stageFlags
			, PushConstantArray const & variables )
			: m_pcb{ stageFlags, variables }
		{
		}
		/**
		*\~english
		*\return
		*	The base offset.
		*\~french
		*\return
		*	Le décalage de base.
		*/
		inline uint32_t getOffset()const
		{
			return getBuffer().getOffset();
		}
		/**
		*\~english
		*\return
		*	The data size.
		*\~french
		*\return
		*	La taille des données.
		*/
		inline uint32_t getSize()const
		{
			return getBuffer().getSize();
		}
		/**
		*\~english
		*\return
		*	The shader stages that will use the push constants in the updated range.
		*\~french
		*\return
		*	Les niveaux de shaders qui vont utiliser les push constants dans l'intervalle mis à jour.
		*/
		inline ShaderStageFlags getStageFlags()const
		{
			return getBuffer().getStageFlags();
		}
		/**
		*\~english
		*\brief
		*	A pointer to the buffer data.
		*\~french
		*\brief
		*	Un pointeur sur les données du tampon.
		*/
		inline T const * getData()const
		{
			return reinterpret_cast< T const * >( getBuffer().getData() );
		}
		/**
		*\~english
		*\brief
		*	A pointer to the buffer data.
		*\~french
		*\brief
		*	Un pointeur sur les données du tampon.
		*/
		inline T * getData()
		{
			return reinterpret_cast< T * >( getBuffer().getData() );
		}
		/**
		*\~english
		*\return
		*	The beginning of the constants array.
		*\~french
		*\return
		*	Le début du tableau de constantes.
		*/
		inline PushConstantArray::const_iterator begin()const
		{
			return getBuffer().begin();
		}
		/**
		*\~english
		*\return
		*	The end of the constants array.
		*\~french
		*\return
		*	La fin du tableau de constantes.
		*/
		inline PushConstantArray::const_iterator end()const
		{
			return getBuffer().end();
		}
		/**
		*\~english
		*\brief
		*	The internal PCB.
		*\~french
		*\brief
		*	Le PCB interne.
		*/
		inline PushConstantsBufferBase const & getBuffer()const
		{
			return m_pcb;
		}
		/**
		*\~english
		*\brief
		*	The internal PCB.
		*\~french
		*\brief
		*	Le PCB interne.
		*/
		inline PushConstantsBufferBase & getBuffer()
		{
			return m_pcb;
		}

	private:
		PushConstantsBufferBase m_pcb;
	};
}

#endif
