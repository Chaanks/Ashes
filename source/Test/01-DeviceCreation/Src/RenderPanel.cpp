#include "RenderPanel.hpp"

#include "Application.hpp"
#include "MainFrame.hpp"

#include <Renderer/Connection.hpp>
#include <Renderer/Device.hpp>

#include <Utils/Transform.hpp>

#include <chrono>

namespace vkapp
{
	RenderPanel::RenderPanel( wxWindow * parent
		, wxSize const & size
		, renderer::Renderer const & renderer )
		: wxPanel{ parent, wxID_ANY, wxDefaultPosition, size }
	{
		try
		{
			doCreateDevice( renderer );
			std::cout << "Logical device created." << std::endl;
		}
		catch ( std::exception & )
		{
			if ( m_device )
			{
				m_device->waitIdle();
			}

			m_device.reset();
			throw;
		}

		DEBUG_WRITE( AppName.ToStdString() + ".log" );
	}

	RenderPanel::~RenderPanel()
	{
		m_device.reset();
	}

	void RenderPanel::doCreateDevice( renderer::Renderer const & renderer )
	{
		m_device = renderer.createDevice( common::makeConnection( this, renderer ) );
	}
}