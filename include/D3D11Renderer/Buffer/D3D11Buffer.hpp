/**
*\file
*	RenderingResources.h
*\author
*	Sylvain Doremus
*/
#ifndef ___D3D11Renderer_Buffer_HPP___
#define ___D3D11Renderer_Buffer_HPP___
#pragma once

#include "D3D11Renderer/D3D11RendererPrerequisites.hpp"

#include <Ashes/Buffer/Buffer.hpp>

namespace d3d11_renderer
{
	class Buffer
		: public ashes::BufferBase
	{
	public:
		Buffer( Device const & device
			, uint32_t size
			, ashes::BufferTargets target );
		~Buffer();
		ashes::MemoryRequirements getMemoryRequirements()const override;

		inline ID3D11Buffer * getBuffer()const
		{
			return m_buffer;
		}

		inline ID3D11UnorderedAccessView * getUnorderedAccessView()const
		{
			return m_unorderedAccessView;
		}

	private:
		void doBindMemory()override;

	private:
		Device const & m_device;
		ID3D11Buffer * m_buffer{ nullptr };
		ID3D11UnorderedAccessView * m_unorderedAccessView{ nullptr };
	};
}

#endif
