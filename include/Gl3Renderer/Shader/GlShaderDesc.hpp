/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#pragma once

#include "Gl3Renderer/GlRendererPrerequisites.hpp"

namespace gl_renderer
{
	struct InputDesc
	{
		std::string name;
		ashes::ConstantFormat format{};
		uint32_t location{ 0u };
	};

	using InputLayout = std::vector< InputDesc >;

	struct ConstantDesc
	{
		std::string name;
		uint32_t location{ 0u };
		ashes::ConstantFormat format{};
		uint32_t size{ 0u };
		uint32_t arraySize{ 1u };
		uint32_t offset{ 0u };
	};

	using ConstantsLayout = std::vector< ConstantDesc >;

	struct ConstantBufferDesc
	{
		std::string name;
		uint32_t binding{ 0u };
		uint32_t size{ 0u };
		ConstantsLayout constants;
	};

	using InterfaceBlockLayout = std::vector< ConstantBufferDesc >;

	struct ShaderDesc
	{
		ashes::ShaderStageFlags stageFlags;
		InputLayout inputLayout;
		ConstantsLayout constantsLayout;
		InterfaceBlockLayout interfaceBlockLayout;
	};

	using ProgramLayout = std::vector< ShaderDesc >;

	struct PushConstantDesc
	{
		ashes::ConstantFormat format{};
		uint32_t location{ 0u };
		uint32_t offset{ 0u };
		uint32_t size{ 0u };
		uint32_t arraySize{ 1u };
	};

	struct PushConstantsDesc
	{
		ashes::ShaderStageFlags stageFlags{};
		uint32_t offset{ 0u };
		uint32_t size{ 0u };
		std::vector< PushConstantDesc > constants;
		std::vector< uint8_t > data;
	};
}
