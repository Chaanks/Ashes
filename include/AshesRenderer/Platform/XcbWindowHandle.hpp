/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___Ashes_XcbWindowHandle_HPP___
#define ___Ashes_XcbWindowHandle_HPP___

#include <xcbint.h>
#include <xcb/xproto.h>

namespace ashes
{
	class IXcbWindowHandle
		: public IWindowHandle
	{
	public:
		IXcbWindowHandle( xcb_connection_t * connection
			, xcb_window_t window )
			: m_connection{ connection }
			, m_window{ window }
		{
		}

		virtual ~IXcbWindowHandle()
		{
		}

		virtual operator bool()
		{
			return m_connection != nullptr && m_window != 0;
		}

		inline xcb_connection_t * getConnection()const
		{
			return m_connection;
		}

		inline xcb_window_t getWindow()const
		{
			return m_window;
		}

	private:
		xcb_connection_t * m_connection;
		xcb_window_t m_window;
	};
}

#endif
