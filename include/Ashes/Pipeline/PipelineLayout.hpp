/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___Ashes_PipelineLayout_HPP___
#define ___Ashes_PipelineLayout_HPP___
#pragma once

#include "Ashes/Pipeline/Pipeline.hpp"
#include "Ashes/Pipeline/ComputePipeline.hpp"

#include "Ashes/Miscellaneous/PushConstantRange.hpp"

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
	protected:
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
			, PushConstantRangeArray const & pushConstantRanges );

	public:
		/**
		*\~english
		*\brief
		*	Destructor.
		*\~french
		*\brief
		*	Destructeur.
		*/
		virtual ~PipelineLayout();
		/**
		*\~english
		*\brief
		*	Creates a graphics pipeline using this layout.
		*\param[in] createInfo
		*	The creation informations.
		*\return
		*	The created pipeline.
		*\~french
		*\brief
		*	Crée un pipeline graphique utilisant ce layout.
		*\param[in] createInfo
		*	Les informations de création.
		*\return
		*	Le pipeline créé.
		*/
		virtual PipelinePtr createPipeline( GraphicsPipelineCreateInfo createInfo )const = 0;
		/**
		*\~english
		*\brief
		*	Creates a compute pipeline using this layout.
		*\param[in] createInfo
		*	The creation informations.
		*\return
		*	The created pipeline.
		*\~french
		*\brief
		*	Crée un pipeline de calcul utilisant ce layout.
		*\param[in] createInfo
		*	Les informations de création.
		*\return
		*	Le pipeline créé.
		*/
		virtual ComputePipelinePtr createPipeline( ComputePipelineCreateInfo createInfo )const = 0;
		/**
		*\~english
		*\brief
		*	Creates a graphics pipeline using this layout.
		*\param[in] stages
		*	The shader stages.
		*\param[in] vertexLayouts
		*	The vertex layout used by the pipeline.
		*\param[in] renderPass
		*	The render pass.
		*\param[in] inputAssemblyState
		*	The input assembly state.
		*\param[in] rasterisationState
		*	The rasterisation state state.
		*\param[in] colourBlendState
		*	The colour blend state.
		*\return
		*	The created pipeline.
		*\~french
		*\brief
		*	Crée un pipeline graphique utilisant ce layout.
		*\param[in] stages
		*	Les niveaux de shader.
		*\param[in] vertexLayouts
		*	Le layout de sommets utilisé par le pipeline.
		*\param[in] renderPass
		*	La passe de rendu.
		*\param[in] inputAssemblyState
		*	L'état d'assemblage des entrées.
		*\param[in] rasterisationState
		*	L'état de rastérisation.
		*\param[in] colourBlendState
		*	L'état de mélange des couleurs.
		*\return
		*	Le pipeline créé.
		*/
		inline PipelinePtr createPipeline( ShaderStageStateArray stages
			, VertexLayoutCRefArray const & vertexLayouts
			, RenderPass const & renderPass
			, InputAssemblyState const & inputAssemblyState
			, RasterisationState const & rasterisationState = RasterisationState{}
			, ColourBlendState const & colourBlendState = ColourBlendState::createDefault() )const
		{
			return createPipeline( GraphicsPipelineCreateInfo
			{
				std::move( stages ),
				VertexInputState::create( vertexLayouts ),
				inputAssemblyState,
				TessellationState{},
				ViewportState{},
				rasterisationState,
				MultisampleState{},
				DepthStencilState{},
				colourBlendState,
				DynamicState{},
				&renderPass,
			} );
		}
		/**
		*\~english
		*\brief
		*	Creates a compute pipeline using this layout.
		*\param[in] stage
		*	The shader stage.
		*\return
		*	The created pipeline.
		*\~french
		*\brief
		*	Crée un pipeline de calcul utilisant ce layout.
		*\param[in] stage
		*	Le niveau de shader.
		*\return
		*	Le pipeline créé.
		*/
		inline ComputePipelinePtr createPipeline( ShaderStageState stage )const
		{
			return createPipeline( ComputePipelineCreateInfo
			{
				std::move( stage )
			} );
		}
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
		inline PushConstantRangeArray const & getPushConstantRanges()const
		{
			return m_pushConstantRanges;
		}

	private:
		Device const & m_device;
		DescriptorSetLayoutCRefArray m_setLayouts;
		PushConstantRangeArray m_pushConstantRanges;
	};
}

#endif
