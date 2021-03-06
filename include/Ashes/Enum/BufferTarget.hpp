﻿/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___Ashes_BufferTarget_HPP___
#define ___Ashes_BufferTarget_HPP___
#pragma once

namespace ashes
{
	/**
	*\~french
	*\brief
	*	Masques de bits décrivant les propriétés pour un type de mémoire.
	*\~english
	*\brief
	*	Bitmask specifying properties for a memory type.
	*/
	enum class BufferTarget
		: uint32_t
	{
		eTransferSrc = 0x00000001,
		eTransferDst = 0x00000002,
		eUniformTexelBuffer = 0x00000004,
		eStorageTexelBuffer = 0x00000008,
		eUniformBuffer = 0x00000010,
		eStorageBuffer = 0x00000020,
		eIndexBuffer = 0x00000040,
		eVertexBuffer = 0x00000080,
		eDispatchIndirectBuffer = 0x00000100,
		eDrawIndirectBuffer = 0x00000200,
		ePackBuffer = 0x00000400,
		eUnpackBuffer = 0x00000800,
	};
	Ashes_ImplementFlag( BufferTarget )
}

#endif
