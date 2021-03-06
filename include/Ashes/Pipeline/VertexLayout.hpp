/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___Ashes_VertexLayout_HPP___
#define ___Ashes_VertexLayout_HPP___
#pragma once

#include "Ashes/Core/Device.hpp"
#include "Ashes/Shader/Attribute.hpp"

#include <vector>

namespace ashes
{
	/**
	*\~french
	*\brief
	*	The layout of a vertex inside a vertex buffer.
	*\~french
	*\brief
	*	Layout d'un sommet dans un tampon de sommets.
	*/
	class VertexLayout
	{
	public:
		/**
		*\~english
		*\brief
		*	Constructor.
		*\param[in] bindingSlot
		*	The binding slot of the associated buffer.
		*\param[in] inputRate
		*	The layout input rate.
		*\param[in] stride
		*	The byte size to go from an element to the next one, in the buffer.
		*\~french
		*\brief
		*	Constructeur.
		*\param[in] bindingSlot
		*	Le point d'attache du tampon associé.
		*\param[in] inputRate
		*	La cadence d'entrée.
		*\param[in] stride
		*	La taille en octets séparant un élément du suivant, dans le tampon.
		*/
		VertexLayout( uint32_t bindingSlot
			, uint32_t stride
			, VertexInputRate inputRate );
		/**
		*\~english
		*\brief
		*	Creates a vertex attribute.
		*\param[in] location
		*	The attribute location, in the shader.
		*\param[in] format
		*	The attribute format, in the shader.
		*\param[in] offset
		*	The attribute location, in the buffer.
		*\~french
		*\brief
		*	Crée un attribut de sommet.
		*\param[in] location
		*	La position de l'attribut, dans le shader.
		*\param[in] format
		*	Le format de l'attribut, dans le shader.
		*\param[in] offset
		*	La position de l'attribut, dans le tampon.
		*/
		void createAttribute( uint32_t location
			, Format format
			, uint32_t offset );
		/**
		*\~english
		*\brief
		*	Creates a group of vertex attributes using the same semantic (matrices, for example).
		*\param[in] count
		*	The attributes count.
		*\param[in] startingLocation
		*	The attributes starting location, in the shader.
		*\param[in] format
		*	The sub-attribute attributes format.
		*\param[in] startingOffset
		*	The attribute location, in the buffer.
		*\~french
		*\brief
		*	Crée un attribut de sommet.
		*\param[in] count
		*	Le nombre d'attributs.
		*\param[in] startingLocation
		*	La position de début des attributs, dans le shader.
		*\param[in] format
		*	Le format de sous attribut des attributs, dans le shader.
		*\param[in] startingOffset
		*	La position de début des attributs, dans le tampon.
		*/
		void createAttributes( uint32_t count
			, uint32_t startingLocation
			, Format format
			, uint32_t startingOffset );
		/**
		*\~french
		*\return
		*	The binding slot of the associated buffer.
		*\~french
		*\return
		*	Le point d'attache du tampon associé.
		*/
		inline uint32_t getBindingSlot()const
		{
			return m_bindingSlot;
		}
		/**
		*\~english
		*\return
		*	The byte size to go from an element to the next one, in the buffer.
		*\~french
		*\return
		*	La taille en octets séparant un élément du suivant, dans le tampon.
		*/
		inline uint32_t getStride()const
		{
			return m_stride;
		}
		/**
		*\~english
		*\return
		*	The input rate.
		*\~french
		*\return
		*	La cadence d'entrée.
		*/
		inline VertexInputRate getInputRate()const
		{
			return m_inputRate;
		}
		/**
		*\~french
		*\return
		*	Le début du tableau d'attributs.
		*\~english
		*\return
		*	The attributes array beginning.
		*/
		inline auto begin()const
		{
			return m_attributes.begin();
		}
		/**
		*\~french
		*\return
		*	Le début du tableau d'attributs.
		*\~english
		*\return
		*	The attributes array beginning.
		*/
		inline auto begin()
		{
			return m_attributes.begin();
		}
		/**
		*\~french
		*\return
		*	La fin du tableau d'attributs.
		*\~english
		*\return
		*	The attributes array end.
		*/
		inline auto end()const
		{
			return m_attributes.end();
		}
		/**
		*\~french
		*\return
		*	La fin du tableau d'attributs.
		*\~english
		*\return
		*	The attributes array end.
		*/
		inline auto end()
		{
			return m_attributes.end();
		}

	private:
		AttributeArray m_attributes;
		uint32_t m_bindingSlot;
		uint32_t m_stride;
		VertexInputRate m_inputRate;
	};
	/**
	*\~english
	*\brief
	*	Creates a vertex layout.
	*\param[in] bindingSlot
	*	The binding slot of the associated buffer.
	*\param[in] inputRate
	*	The layout input rate.
	*\~french
	*\brief
	*	Crée un layout de sommet.
	*\param[in] bindingSlot
	*	Le point d'attache du tampon associé.
	*\param[in] inputRate
	*	La cadence d'entrée.
	*/
	template< typename T >
	VertexLayoutPtr makeLayout( uint32_t bindingSlot
		, VertexInputRate inputRate = VertexInputRate::eVertex )
	{
		return std::make_unique< VertexLayout >( bindingSlot
			, uint32_t( sizeof( T ) )
			, inputRate );
	}
}

#endif
