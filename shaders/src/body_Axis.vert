//
// body_Axis
//

#version 420
#pragma debug(on)
#pragma optimize(off)
#pragma optionNV(fastprecision off)

layout (location=0)in vec3 position;

layout (binding=0) uniform uMVP {mat4 MVP;};

void main()
{
	gl_Position = MVP * vec4(position,1.0);
}

