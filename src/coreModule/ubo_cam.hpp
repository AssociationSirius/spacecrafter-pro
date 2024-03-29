#ifndef UBOCAM_HPP_INCLUDED
#define UBOCAM_HPP_INCLUDED

#include "tools/vecmath.hpp"

//Shader part
/*
layout (std140) uniform cam_block
{
	ivec4 viewport;
	ivec4 viewport_center;
	vec4 main_clipping_fov;
	mat4 MVP2D;
	float ambient;
	float time;
	bool allsphere
};
*/

#include "EntityCore/Forward.hpp"
#include "EntityCore/Resource/SharedBuffer.hpp"

struct UBOData {
	Vec4i viewport;
	Vec4i viewport_center;
	Vec4f main_clipping_fov;
	Mat4f MVP2D;
	float ambient;
	float time;
	VkBool32 allsphere;
};

class UBOCam {
private:
	SharedBuffer<UBOData> UBOdata;
	PipelineLayout *globalLayout;
	Set *globalSet;
	float time = 0;
	bool lastAllsphere = false;
public:
	UBOCam();
	~UBOCam();
	void update();

	void setClippingFov(const Vec3f &v) {
		UBOdata->main_clipping_fov= v;
	}

	void setViewportCenter(const Vec3i &v) {
		UBOdata->viewport_center = v;
	}

	void setViewport(const Vec4i &v) {
		UBOdata->viewport = v;
	}

	void setMVP2D(const Mat4f &v) {
		UBOdata->MVP2D = v;
		UBOdata->MVP2D[0][2] = UBOdata->MVP2D[1][2] = UBOdata->MVP2D[2][2] = 0.f;
		UBOdata->MVP2D[3][2] = 1.f;
	}

	void setTime(float time) {
		this->time = time;
		UBOdata->time = time;
	}

	void setAmbientLight(float _ambient) {
		UBOdata->ambient = _ambient;
	}

	float getAmbientLight() {
		return UBOdata->ambient;
	}

	void setAllsphere(bool state) {
		if (state != lastAllsphere) {
			UBOdata->allsphere = state;
			lastAllsphere = state;
		}
	}

	static SharedBuffer<UBOData> *ubo;
};

#endif // UBOCAM_HPP_INCLUDED
