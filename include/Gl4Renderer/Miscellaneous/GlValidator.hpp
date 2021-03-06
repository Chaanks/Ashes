/**
*\file
*	Image.h
*\author
*	Sylvain Doremus
*/
#ifndef ___GlRenderer_Validator_HPP___
#define ___GlRenderer_Validator_HPP___
#pragma once

#include "Gl4Renderer/Shader/GlShaderDesc.hpp"

namespace gl_renderer
{
	InterfaceBlockLayout getInterfaceBlockLayout( ContextLock const & context
		, GLuint program );
	ConstantsLayout getConstantsLayout( ContextLock const & context
		, GLuint program );
	inline ShaderDesc getShaderDesc( ContextLock const & context
		, GLuint program )
	{
		return
		{
			0u,
			getConstantsLayout( context, program ),
			getInterfaceBlockLayout( context, program )
		};
	}

	void validatePipeline( ContextLock const & context
		, PipelineLayout const & layout
		, GLuint program
		, ashes::VertexInputState const & vertexInputState
		, ashes::RenderPass const & renderPass );
}

#endif
