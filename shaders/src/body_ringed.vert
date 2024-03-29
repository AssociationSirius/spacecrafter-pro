//
// body ringed
//
#version 420
#pragma debug(on)
#pragma optimize(off)
#pragma optionNV(fastprecision off)

layout (binding=0) uniform globalVertProj {
	mat4 ModelViewMatrix;
	mat4 NormalMatrix;
	vec3 clipping_fov;
	float planetRadius;
	vec3 LightPosition;
	float planetScaledRadius;
	float planetOneMinusOblateness;
};

layout (binding=2) uniform custom {
	mat4 ModelViewMatrixInverse;
};

#include <cam_block.glsl>
#include <fisheye.glsl>

//layout
layout (location=0)in vec3 position;
layout (location=1)in vec2 texcoord;
layout (location=2)in vec3 normal;


//out
layout (location=0) out vec2 TexCoord;
layout (location=1) out float Ambient;

//layout (location=2) out vec3 Normal;
layout (location=2) out vec3 Position;
layout (location=3) out float NdotL;
layout (location=4) out vec3 Light;
layout (location=5) out vec3 ModelLight;
layout (location=6) out vec3 OriginalPosition;

void main()
{
	//glPosition
	vec3 Position0;
	Position0.x =position.x * planetScaledRadius;
	Position0.y =position.y * planetScaledRadius;
	Position0.z =position.z * planetScaledRadius * planetOneMinusOblateness;
	gl_Position = fisheyeProject(Position0, clipping_fov);

    //Light
	vec3 positionL = planetRadius * position ;
	positionL.z = positionL.z * planetOneMinusOblateness;
	OriginalPosition = positionL;
	Position = vec3(ModelViewMatrix * vec4(positionL,1.0));
	Light = normalize(LightPosition - Position);

	//Other
	vec3 Normal = normalize(mat3(NormalMatrix) * normal);
	ModelLight = vec3(ModelViewMatrixInverse * vec4(Light,1.0));
	NdotL = dot(Normal, Light);
	TexCoord = texcoord;
	Ambient = ambient;
}
