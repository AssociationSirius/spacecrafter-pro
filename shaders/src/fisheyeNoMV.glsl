//////////////////// PROJECTION FISHEYE ////////////////////////////////
#extension GL_KHR_shader_subgroup_vote : enable

#define M_PI 3.14159265358979323846

#include <my_atan.glsl>

// fisheyeProject without ModelView projection
vec4 fisheyeProjectNoMV(vec3 win, in vec3 clipping_fov)
{
	float zNear=clipping_fov[0];
	float zFar=clipping_fov[1];
	float fisheye_scale_factor = 360./clipping_fov[2];

    float rq1 = win.x*win.x+win.y*win.y;

    float depth = sqrt(rq1 + win.z*win.z);

	win /= sqrt(rq1)+1e-30; // Don't divide by zero
	float a;

	if (usingDouble && subgroupAny((clipping_fov[2] < 0.03f) || (win.z > 5.f))) { // Don't use both atan and my_atan in a subgroup, it would reduce performances
		a = float(my_atan(win.z));
	} else {
		a = atan(win.z);
	}
	float f = fma(a, 1.f/M_PI, 0.5f) * fisheye_scale_factor;

    depth = (fisheye_scale_factor > 1.3 && a > M_PI*0.4f) ? -1e30 : (depth - zNear) / (zFar-zNear);
    return vec4(win.x * f, win.y * f, depth, 1.);
}
