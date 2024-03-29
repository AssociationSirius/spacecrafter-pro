//
// my earth tessellation
//

#version 430 core
#pragma debug(on)
#pragma optimize(off)

layout(vertices=3) out;

//NEW UNIFORMS
layout (binding=2) uniform globalTescGeom {
	uniform ivec3 TesParam;         // [min_tes_lvl, max_tes_lvl, coeff_altimetry]
};

layout(location=0) in vec3 PositionIn[];
layout(location=1) in vec2 TexCoordIn[];
layout(location=2) in vec3 NormalIn[];
layout(location=3) in vec4 glPositionIn[];

layout(location=0) out vec3 PositionOut[];
layout(location=1) out vec2 TexCoordOut[];
layout(location=2) out vec3 NormalOut[];
    //~ out vec3 tangent;

#define ID gl_InvocationID

void main(void)
{
    TexCoordOut[ID] = TexCoordIn[ID];
    NormalOut[ID] = NormalIn[ID];
    PositionOut[ID] = PositionIn[ID];
    if (ID == 0) {
        vec4 center = (glPositionIn[0] + glPositionIn[1] + glPositionIn[2]) / 3;
        float centerDistance = sqrt(center.x * center.x + center.y * center.y);
        vec2 v0 = glPositionIn[0].xy;
        vec2 v1 = glPositionIn[1].xy;
        vec2 v2 = glPositionIn[2].xy;
        vec3 tes = vec3(distance(v1, v2),
                        distance(v0, v2),
                        distance(v0, v1));
        v1 -= v0;
        v2 -= v0;
        if (centerDistance > (1 + (tes.x + tes.y + tes.z)/2 + max(0, dot(center.xy, center.xy - center.zw) / centerDistance)) * float(v1.x * v2.y > v1.y * v2.x)) {
            gl_TessLevelInner[0]=0;
            gl_TessLevelOuter[0]=0;
            gl_TessLevelOuter[1]=0;
            gl_TessLevelOuter[2]=0;
            return;
	}
        tes = clamp(tes * 128, TesParam[0], TesParam[1]);

        gl_TessLevelOuter[0] = tes[0];
        gl_TessLevelOuter[1] = tes[1];
        gl_TessLevelOuter[2] = tes[2];

        gl_TessLevelInner[0]=(tes[0] + tes[1] + tes[2])/3;
    }
}
