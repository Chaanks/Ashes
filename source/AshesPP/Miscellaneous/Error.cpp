/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "AshesPP/AshesPPPrerequisites.hpp"

#include <AshesRenderer/Util/Exception.hpp>

#include <map>
#include <atomic>
#include <thread>

namespace ashes
{
	void checkError( VkResult errCode
		, char const * const text )
	{
		bool result = errCode == VK_SUCCESS;

		if ( !result )
		{
			throw Exception{ errCode, text };
		}
	}
}
