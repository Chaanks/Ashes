/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#pragma once

#include <Ashes/AshesPrerequisites.hpp>

namespace vk_renderer
{
	/**
	*\brief
	*	Convertit un ashes::CommandPoolCreateFlags en VkCommandPoolCreateFlags.
	*\param[in] flags
	*	Le ashes::CommandPoolCreateFlags.
	*\return
	*	Le VkCommandPoolCreateFlags.
	*/
	VkCommandPoolCreateFlags convert( ashes::CommandPoolCreateFlags const & flags );
}
