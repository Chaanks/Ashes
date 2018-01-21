#version 450

layout( location = 0 ) in vec4 position;
layout( location = 1 ) in float texcoord;

out gl_PerVertex
{
  vec4 gl_Position;
};

layout( location = 0 ) out float vtx_texcoord;

void main()
{
	gl_Position = position;
#ifndef VULKAN
	gl_Position.y = -gl_Position.y;
#endif
	vtx_texcoord = texcoord;
}