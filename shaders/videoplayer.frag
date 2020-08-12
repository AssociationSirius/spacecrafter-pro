//
//	VIDEO PLAYER
//
#version 420
#pragma debug(on)
#pragma optimize(off)

layout (binding=0) uniform sampler2D s_texture_y;
layout (binding=1) uniform sampler2D s_texture_u;
layout (binding=2) uniform sampler2D s_texture_v;

#include <convertToRGB.glsl>

smooth in vec2 TexCoord;

uniform bool transparency;
uniform vec4 noColor;
uniform float fader;

out vec4 FragColor;

void main(void)
{
    vec3 tex_color = convertToRGB(s_texture_y, s_texture_u, s_texture_v, TexCoord);

	if (transparency) {
		vec3 diffVec = abs(tex_color-noColor.rgb);
		float delta = noColor.a;
		if ((diffVec.r<delta) && (diffVec.g<delta) && (diffVec.b<delta))
			discard;
	}

	FragColor = vec4(tex_color, fader);
}
