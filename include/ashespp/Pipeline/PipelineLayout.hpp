/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___AshesPP_PipelineLayout_HPP___
#define ___AshesPP_PipelineLayout_HPP___
#pragma once

#include "ashespp/Pipeline/GraphicsPipeline.hpp"
#include "ashespp/Pipeline/ComputePipeline.hpp"

namespace ashes
{
	/**
	*\~english
	*\brief
	*	The pipeline layout.
	*\~french
	*\brief
	*	Layout de pipeline.
	*/
	class PipelineLayout
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
			, DescriptorSetLayoutCRefArray const & setLayouts
			, VkPushConstantRangeArray const & pushConstantRanges );
		/**
		*\~english
		*\brief
		*	Destructor.
		*\~french
		*\brief
		*	Destructeur.
		*/
		~PipelineLayout();
		/**
		*\~english
		*\return
		*	The descriptor sets layouts.
		*\~french
		*\return
		*	Les layouts d'ensembles de descripteurs.
		*/
		inline DescriptorSetLayoutCRefArray const & getDescriptorSetsLayouts()const
		{
			return m_setLayouts;
		}
		/**
		*\~english
		*\return
		*	The push constant ranges.
		*\~french
		*\return
		*	Les intervalles de push constants.
		*/
		inline VkPushConstantRangeArray const & getPushConstantRanges()const
		{
			return m_pushConstantRanges;
		}
		/**
		*\~french
		*\brief
		*	Conversion implicite vers VkPipelineLayout.
		*\~english
		*\brief
		*	VkPipelineLayout implicit cast operator.
		*/
		inline operator VkPipelineLayout const & ()const
		{
			return m_internal;
		}

	private:
		Device const & m_device;
		VkPipelineLayout m_internal{ VK_NULL_HANDLE };
		DescriptorSetLayoutCRefArray m_setLayouts;
		VkPushConstantRangeArray m_pushConstantRanges;
	};
}

#endif