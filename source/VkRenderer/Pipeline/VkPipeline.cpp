#include "Pipeline/VkPipeline.hpp"

#include "Core/VkDevice.hpp"
#include "Pipeline/VkPipelineLayout.hpp"
#include "Pipeline/VkSpecialisationInfo.hpp"
#include "Pipeline/VkSpecialisationMapEntry.hpp"
#include "Pipeline/VkVertexInputAttributeDescription.hpp"
#include "Pipeline/VkVertexInputBindingDescription.hpp"
#include "Pipeline/VkVertexInputState.hpp"
#include "RenderPass/VkRenderPass.hpp"
#include "Shader/VkAttribute.hpp"
#include "Shader/VkShaderModule.hpp"

#include <algorithm>

namespace vk_renderer
{
	Pipeline::Pipeline( Device const & device
		, ashes::PipelineLayout const & layout
		, ashes::GraphicsPipelineCreateInfo createInfo )
		: ashes::Pipeline{ device
			, layout
			, std::move( createInfo ) }
		, m_device{ device }
		, m_layout{ static_cast< PipelineLayout const & >( layout ) }
		, m_vertexAttributes{ convert< VkVertexInputAttributeDescription >( m_createInfo.vertexInputState.vertexAttributeDescriptions ) }
		, m_vertexBindings{ convert< VkVertexInputBindingDescription >( m_createInfo.vertexInputState.vertexBindingDescriptions ) }
		, m_vertexInputState{ convert( m_createInfo.vertexInputState, m_vertexAttributes, m_vertexBindings ) }
		, m_renderPass{ static_cast< RenderPass const & >( *m_createInfo.renderPass ) }
		, m_inputAssemblyState{ convert( m_createInfo.inputAssemblyState ) }
		, m_rasterisationState{ convert( m_createInfo.rasterisationState ) }
		, m_colourBlendStateAttachments{ convert< VkPipelineColorBlendAttachmentState >( m_createInfo.colourBlendState.attachs.begin(), m_createInfo.colourBlendState.attachs.end() ) }
		, m_colourBlendState{ convert( m_createInfo.colourBlendState, m_colourBlendStateAttachments ) }
		, m_multisampleState{ convert( m_createInfo.multisampleState ) }
		, m_viewportState{ convert( m_createInfo.viewportState, m_viewports, m_scissors ) }
	{
		if ( bool( m_createInfo.dynamicState ) )
		{
			convert( m_createInfo.dynamicState.value(), m_dynamicStates );
		}

		if ( m_createInfo.depthStencilState )
		{
			m_depthStencilState = convert( m_createInfo.depthStencilState.value() );
		}

		if ( m_createInfo.tessellationState )
		{
			m_tessellationState = convert( m_createInfo.tessellationState.value() );
		}

		// Les informations liées aux shaders utilisés.
		uint32_t index = 0;
		std::vector< VkPipelineShaderStageCreateInfo > shaderStages;
		m_specialisationEntries.resize( m_createInfo.stages.size() );

		for ( auto & state : m_createInfo.stages )
		{
			auto & module = static_cast< ShaderModule const & >( *state.module );

			if ( state.specialisationInfo )
			{
				auto & info = *state.specialisationInfo;
				m_specialisationEntries[index] = convert< VkSpecializationMapEntry >( info.begin(), info.end() );
				m_specialisationInfos[module.getStage()] = convert( info, m_specialisationEntries[index] );
				shaderStages.push_back( convert( state, &m_specialisationInfos[module.getStage()] ) );
			}
			else
			{
				shaderStages.push_back( convert( state ) );
			}

			++index;
		}

		// Les états dynamiques, le cas échéant
		if ( m_viewports.empty() )
		{
			assert( m_dynamicStates.end() != std::find( m_dynamicStates.begin(), m_dynamicStates.end(), VK_DYNAMIC_STATE_VIEWPORT ) );
		}

		if ( m_scissors.empty() )
		{
			assert( m_dynamicStates.end() != std::find( m_dynamicStates.begin(), m_dynamicStates.end(), VK_DYNAMIC_STATE_SCISSOR ) );
		}

		VkPipelineDynamicStateEnableCreateInfo dynamicState
		{
			VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,         // sType
			nullptr,                                                      // pNext
			0,                                                            // flags
			static_cast< uint32_t >( m_dynamicStates.size() ),            // dynamicStateCount
			m_dynamicStates.data()                                        // pDynamicStateEnables
		};

		// Enfin, on crée le pipeline !!
		VkGraphicsPipelineCreateInfo pipeline
		{
			VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
			nullptr,
			0,                                                            // flags
			static_cast< uint32_t >( shaderStages.size() ),               // stageCount
			shaderStages.data(),                                          // pStages
			&m_vertexInputState,                                          // pVertexInputState;
			&m_inputAssemblyState,                                        // pInputAssemblyState
			m_tessellationState                                           // pTessellationState
				? &m_tessellationState.value()
				: nullptr,
			&m_viewportState,                                             // pViewportState
			&m_rasterisationState,                                        // pRasterizationState
			&m_multisampleState,                                          // pMultisampleState
			m_depthStencilState                                           // pDepthStencilState
				? &m_depthStencilState.value()
				: nullptr,
			&m_colourBlendState,                                          // pColorBlendState
			m_dynamicStates.empty() ? nullptr : &dynamicState,            // pDynamicStateEnable
			m_layout,                                                     // layout
			m_renderPass,                                                 // renderPass
			0,                                                            // subpass
			VK_NULL_HANDLE,                                               // basePipelineHandle
			-1                                                            // basePipelineIndex
		};
		DEBUG_DUMP( pipeline );
		DEBUG_WRITE( "pipeline.log" );
		auto res = m_device.vkCreateGraphicsPipelines( m_device
			, VK_NULL_HANDLE
			, 1
			, &pipeline
			, nullptr
			, &m_pipeline );
		checkError( res, "GraphicsPipeline creation" );
	}

	Pipeline::~Pipeline()
	{
		m_device.vkDestroyPipeline( m_device, m_pipeline, nullptr );
	}
}
