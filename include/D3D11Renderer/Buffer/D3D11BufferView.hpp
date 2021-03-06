/**
*\file
*	TestBufferView.h
*\author
*	Sylvain Doremus
*/
#ifndef ___D3D11Renderer_BufferView_HPP___
#define ___D3D11Renderer_BufferView_HPP___
#pragma once

#include "D3D11Renderer/D3D11RendererPrerequisites.hpp"

#include <Ashes/Buffer/BufferView.hpp>

namespace d3d11_renderer
{
	class BufferView
		: public ashes::BufferView
	{
	public:
		BufferView( Device const & device
			, Buffer const & buffer
			, ashes::Format format
			, uint32_t offset
			, uint32_t range );
		~BufferView();

		inline ID3D11ShaderResourceView * getView()const
		{
			return m_view;
		}

	private:
		ID3D11ShaderResourceView * m_view;
	};
}

#endif
