/*
This file belongs to Ashes.
See LICENSE file in root folder
*/
#pragma once

#include "D3D11Renderer/Command/Commands/D3D11CommandBase.hpp"

namespace ashes::d3d11
{
	/**
	*\brief
	*	Classe de base d'une commande.
	*/
	class BindIndexBufferCommand
		: public CommandBase
	{
	public:
		/**
		*\brief
		*	Constructeur.
		*/
		BindIndexBufferCommand( Device const & device
			, Buffer const & ibo
			, uint64_t offset
			, VkIndexType indexType );

		void apply( Context const & context )const;
		void remove( Context const & context )const;
		CommandPtr clone()const;

	private:
		Buffer const & m_ibo;
		UINT m_offset;
		DXGI_FORMAT m_indexType;
	};
}