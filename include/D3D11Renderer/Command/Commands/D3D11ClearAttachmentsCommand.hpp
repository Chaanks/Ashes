/*
This file belongs to Ashes.
See LICENSE file in root folder
*/
#pragma once

#include "D3D11Renderer/Command/Commands/D3D11CommandBase.hpp"

#include <Ashes/RenderPass/ClearAttachment.hpp>
#include <Ashes/RenderPass/ClearRect.hpp>

namespace ashes::d3d11
{
	struct ClearAttachmentView
	{
		ashes::ClearAttachment clear;
		ID3D11View * view;
	};
	class ClearAttachmentsCommand
		: public CommandBase
	{
	public:
		ClearAttachmentsCommand( Device const & device
			, RenderPass const & renderPass
			, ashes::SubpassDescription const & subpass
			, FrameBuffer const & framebuffer
			, ashes::ClearAttachmentArray const & clearAttaches
			, ashes::ClearRectArray const & clearRects );

		void apply( Context const & context )const;
		CommandPtr clone()const;

	private:
		ashes::ClearRectArray m_clearRects;
		std::vector< ClearAttachmentView > m_clearViews;
	};
}
