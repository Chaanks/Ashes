/*
This file belongs to Renderer.
See LICENSE file in root folder.
*/
#pragma once

#include <Renderer/AttributeBase.hpp>

#include <VkLib/VertexAttribute.hpp>

namespace vk_renderer
{
	/**
	*\brief
	*	Classe encapsulant le concept d'attribut de sommet.
	*/
	class AttributeBase
		: public renderer::AttributeBase
	{
	public:
		/**
		*\brief
		*	Constructeur.
		*\param[in] layout
		*	Le layout de sommets associé.
		*\param[in] location
		*	La position de l'attribut dans le shader.
		*\param[in] offset
		*	La position de l'attribut dans le tampon.
		*/
		AttributeBase( renderer::VertexLayout & layout
			, renderer::AttributeFormat format
			, uint32_t location
			, uint32_t offset );

	private:
		vk::VertexAttribute const & m_attribute;
	};
}