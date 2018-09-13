layout( location = 0 ) in vec4 position;

out gl_PerVertex
{
  vec4 gl_Position;
};

layout( set=0, binding=0 ) uniform Matrix
{
	mat4 mtxViewProjection;
};

layout( location = 0 ) out vec3 vtx_position;

void main()
{
	vtx_position = ashesScalePosition( position ).xyz;
	gl_Position = mtxViewProjection * position;
}
