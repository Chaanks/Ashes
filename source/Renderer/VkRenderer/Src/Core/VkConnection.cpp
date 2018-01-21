/*
This file belongs to Renderer.
See LICENSE file in root folder.
*/
#include "Core/VkConnection.hpp"

#include "Core/VkPhysicalDevice.hpp"
#include "Core/VkRenderer.hpp"

#include <Core/PlatformWindowHandle.hpp>

#include "vulkan/vk_platform.h"

namespace vk_renderer
{
	Connection::Connection( Renderer const & renderer
		, uint32_t deviceIndex
		, renderer::WindowHandle && handle )
		: renderer::Connection{ renderer, deviceIndex, std::move( handle ) }
		, m_renderer{ renderer }
		, m_gpu{ renderer.getPhysicalDevice( deviceIndex ) }
	{
		doCreatePresentSurface();
		doRetrievePresentationInfos();
	}

	Connection::~Connection()
	{
		if ( m_presentSurface != VK_NULL_HANDLE )
		{
			vk::DestroySurfaceKHR( m_renderer
				, m_presentSurface
				, nullptr );
		}
	}

#if RENDERLIB_WIN32

	void Connection::doCreatePresentSurface()
	{
		VkWin32SurfaceCreateInfoKHR createInfo
		{
			VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
			nullptr,
			0,
			m_handle.getInternal< renderer::IMswWindowHandle >().getHinstance(),
			m_handle.getInternal< renderer::IMswWindowHandle >().getHwnd(),
		};
		DEBUG_DUMP( createInfo );
		auto res = vk::CreateWin32SurfaceKHR( m_renderer
			, &createInfo
			, nullptr
			, &m_presentSurface );

		if ( !checkError( res ) )
		{
			throw std::runtime_error{ "Presentation surface creation failed: " + getLastError() };
		}
	}

#elif RENDERLIB_XCB

	void Connection::doCreatePresentSurface()
	{
		VkXcbSurfaceCreateInfoKHR createInfo
		{
			VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
			nullptr,
			0,
			m_handle.getInternal< renderer::IXcbWindowHandle >().getConnection(),
			m_handle.getInternal< renderer::IXcbWindowHandle >().getHandle(),
		};
		auto res = CreateXcbSurfaceKHR( m_renderer
			, &createInfo
			, nullptr
			, &m_presentSurface );

		if ( !checkError( res ) )
		{
			throw std::runtime_error{ "Presentation surface creation failed: " + getLastError() };
		}
	}

#else

	void Connection::doCreatePresentSurface()
	{
		VkXlibSurfaceCreateInfoKHR createInfo
		{
			VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
			nullptr,
			0,
			m_handle.getInternal< renderer::IXWindowHandle >().getDisplay(),
			m_handle.getInternal< renderer::IXWindowHandle >().getDrawable(),
		};
		auto res = CreateXlibSurfaceKHR( m_renderer
			, &createInfo
			, nullptr
			, &m_presentSurface );

		if ( !checkError( res ) )
		{
			throw std::runtime_error{ "Presentation surface creation failed: " + getLastError() };
		}
	}

#endif

	VkSurfaceCapabilitiesKHR Connection::getSurfaceCapabilities()const
	{
		// On r�cup�re les capacit�s de la surface.
		VkSurfaceCapabilitiesKHR caps;
		auto res = vk::GetPhysicalDeviceSurfaceCapabilitiesKHR( m_gpu
			, m_presentSurface
			, &caps );

		if ( !checkError( res ) )
		{
			throw std::runtime_error{ "Surface capabilities check failed: " + getLastError() };
		}

		return caps;
	}

	void Connection::doRetrievePresentationInfos()
	{
		// Parcours des propri�t�s des files, pour v�rifier leur support de la pr�sentation.
		std::vector< VkBool32 > supportsPresent( static_cast< uint32_t >( m_gpu.getQueueProperties().size() ) );
		uint32_t i{ 0u };
		m_graphicsQueueFamilyIndex = std::numeric_limits< uint32_t >::max();
		m_presentQueueFamilyIndex = std::numeric_limits< uint32_t >::max();

		for ( auto & present : supportsPresent )
		{
			vk::GetPhysicalDeviceSurfaceSupportKHR( m_gpu
				, i
				, m_presentSurface
				, &present );

			if ( ( m_gpu.getQueueProperties()[i].queueCount > 0 ) &&
				( m_gpu.getQueueProperties()[i].queueFlags & VK_QUEUE_GRAPHICS_BIT ) )
			{
				// Tout d'abord on choisit une file graphique
				if ( m_graphicsQueueFamilyIndex == std::numeric_limits< uint32_t >::max() )
				{
					m_graphicsQueueFamilyIndex = i;
				}

				// Si une file supporte les graphismes et la pr�sentation, on la pr�f�re.
				if ( present )
				{
					m_graphicsQueueFamilyIndex = i;
					m_presentQueueFamilyIndex = i;
					break;
				}
			}

			++i;
		}

		if ( m_presentQueueFamilyIndex == std::numeric_limits< uint32_t >::max() )
		{
			// Pas de file supportant les deux, on a donc 2 files distinctes.
			for ( size_t i = 0; i < m_gpu.getQueueProperties().size(); ++i )
			{
				if ( supportsPresent[i] )
				{
					m_presentQueueFamilyIndex = static_cast< uint32_t >( i );
					break;
				}
			}
		}

		// Si on n'en a pas trouv�, on g�n�re une erreur.
		if ( m_graphicsQueueFamilyIndex == std::numeric_limits< uint32_t >::max()
			|| m_presentQueueFamilyIndex == std::numeric_limits< uint32_t >::max() )
		{
			throw std::runtime_error{ "Could not find appropriate queue families" };
		}
	}
}