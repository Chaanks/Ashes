/*
This file belongs to Ashes.
See LICENSE file in root folder
*/
#pragma once

#include "Gl4Renderer/GlRendererPrerequisites.hpp"

#include <Ashes/Pipeline/PipelineLayout.hpp>

namespace gl_renderer
{
	/**
	*\brief
	*	Layout de pipeline.
	*/
	class PipelineLayout
		: public ashes::PipelineLayout
	{
	public:
		/**
		*\~english
		*\brief
		*	Constructor.
		*\param[in] device
		*	The parent LogicalDevice.
		*\param[in] setLayouts
		*	The descriptor sets layouts.
		*\param[in] pushConstantRanges
		*	The push constants ranges.
		*\~french
		*\brief
		*	Constructeur.
		*\param[in] device
		*	Le LogicalDevice parent.
		*\param[in] setLayouts
		*	Les layouts des descripteurs du pipeline.
		*\param[in] pushConstantRanges
		*	Les intervalles de push constants.
		*/
		PipelineLayout( Device const & device
			, ashes::DescriptorSetLayoutCRefArray const & setLayouts
			, ashes::PushConstantRangeArray const & pushConstantRanges );
		/**
		*\copydoc		ashes::PipelineLayout::createPipeline
		*/
		ashes::PipelinePtr createPipeline( ashes::GraphicsPipelineCreateInfo createInfo )const override;
		/**
		*\copydoc	ashes::PipelineLayout::createPipeline
		*/
		ashes::ComputePipelinePtr createPipeline( ashes::ComputePipelineCreateInfo createInfo )const override;

	private:
		Device const & m_device;
	};
}
