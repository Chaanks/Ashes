﻿/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___Ashes_MipmapMode_HPP___
#define ___Ashes_MipmapMode_HPP___
#pragma once

namespace ashes
{
	/**
	*\brief
	*	Enumération des modes de mipmap.
	*/
	enum class MipmapMode
	{
		eNone,
		eNearest,
		eLinear,
		Ashes_EnumBounds( eNearest )
	};
	/**
	*\~english
	*\brief
	*	Gets the name of the given element type.
	*\param[in] value
	*	The element type.
	*\return
	*	The name.
	*\~french
	*\brief
	*	Récupère le nom du type d'élément donné.
	*\param[in] value
	*	Le type d'élément.
	*\return
	*	Le nom.
	*/
	inline std::string getName( MipmapMode value )
	{
		switch ( value )
		{
		case MipmapMode::eNone:
			return "none";

		case MipmapMode::eNearest:
			return "nearest";

		case MipmapMode::eLinear:
			return "linear";

		default:
			assert( false && "Unsupported MipmapMode." );
			throw std::runtime_error{ "Unsupported MipmapMode" };
		}

		return 0;
	}
}

#endif
