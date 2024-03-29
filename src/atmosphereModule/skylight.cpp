/*
 * Copyright (C) 2003 Fabien Chereau
 * Copyright (C) 2009 Digitalis Education Solutions, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Spacecrafter is a free open project of of LSS team
 * See the TRADEMARKS file for free open project usage requirements.
 *
 */

// Class which compute the daylight sky color
// Fast implementation of the algorithm from the article
// "A Practical Analytic Model for Daylight" by A. J. Preetham, Peter Shirley and Brian Smits.

#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "atmosphereModule/skylight.hpp"
#include "tools/sc_const.hpp"


Skylight::Skylight()
{
	setComputeTypeColor(ATMOSPHERE_MODEL::EARTH_MODEL);
}

Skylight::~Skylight()
{
}


void Skylight::setParams(float _sun_zenith_angle, float _turbidity)
{
	// Set the two main variables
	thetas = _sun_zenith_angle;
	T = _turbidity;

	// Precomputation of the distribution coefficients and zenith luminances/color
	computeZenithLuminance();
	computeZenithEarthColor();
	computeLuminanceDistributionCoefs();
	computeColorDistributionCoefs();

	// Precompute everything possible to increase the get_CIE_value() function speed
	float cos_thetas = cosf(thetas);
	term_x = zenith_color_x   / ((1.f + Ax * expf(Bx)) * (1.f + Cx * expf(Dx*thetas) + Ex * cos_thetas * cos_thetas));
	term_y = zenith_color_y   / ((1.f + Ay * expf(By)) * (1.f + Cy * expf(Dy*thetas) + Ey * cos_thetas * cos_thetas));
	term_Y = zenith_luminance / ((1.f + AY * expf(BY)) * (1.f + CY * expf(DY*thetas) + EY * cos_thetas * cos_thetas));

}

void Skylight::setParamsv(const float * _sun_pos, float _turbidity)
{
	// Store sun position
	sun_pos[0] = _sun_pos[0];
	sun_pos[1] = _sun_pos[1];
	sun_pos[2] = _sun_pos[2];

	// Set the two main variables
	thetas = M_PI_2 - asinf(sun_pos[2]);
	T = _turbidity;

	// Precomputation of the distribution coefficients and zenith luminances/color
	computeZenithLuminance();
	currentComputeFunction();
	computeLuminanceDistributionCoefs();
	computeColorDistributionCoefs();

	// Precompute everything possible to increase the get_CIE_value() function speed
	float cos_thetas = sun_pos[2];
	term_x = zenith_color_x   / ((1.f + Ax * expf(Bx)) * (1.f + Cx * expf(Dx*thetas) + Ex * cos_thetas * cos_thetas));
	term_y = zenith_color_y   / ((1.f + Ay * expf(By)) * (1.f + Cy * expf(Dy*thetas) + Ey * cos_thetas * cos_thetas));
	term_Y = zenith_luminance / ((1.f + AY * expf(BY)) * (1.f + CY * expf(DY*thetas) + EY * cos_thetas * cos_thetas));
}

// Compute CIE luminance for zenith in cd/m^2
inline void Skylight::computeZenithLuminance(void)
{
	zenith_luminance = 1000.f * ((4.0453f*T - 4.9710f) * tanf( (0.4444f - T/120.f) * (M_PI-2.f*thetas) ) -
	                             0.2155f*T + 2.4192f);
	if (zenith_luminance<=0.f) zenith_luminance=0.00000000001;
}

void Skylight::setComputeTypeColor(ATMOSPHERE_MODEL type)
{
	switch (type) {
	case ATMOSPHERE_MODEL::MARS_MODEL : 
		currentComputeFunction = std::bind(&Skylight::computeZenithMarsColor, this);
		break;
	case ATMOSPHERE_MODEL::VENUS_MODEL : 
		currentComputeFunction = std::bind(&Skylight::computeZenithVenusColor, this);
		break;
	case ATMOSPHERE_MODEL::EARTH_MODEL : 
		currentComputeFunction = std::bind(&Skylight::computeZenithEarthColor, this);
		break;
	default:
		currentComputeFunction = std::bind(&Skylight::computeZenithEarthColor, this);
		break;
	}
}


// Compute CIE x and y color components
inline void Skylight::computeZenithEarthColor()
{
	static float thetas2;
	static float thetas3;
	static float T2;

	thetas2 = thetas * thetas;
	thetas3 = thetas2 * thetas;
	T2 = T * T;

	zenith_color_x = (0.00166f*thetas3 - 0.00375f*thetas2 + 0.00209f*thetas) * T2 +
	                 (-0.02903f*thetas3 + 0.06377f*thetas2 - 0.03202f*thetas + 0.00394f) * T +
	                 ( 0.11693f*thetas3 - 0.21196f*thetas2 + 0.06052f*thetas + 0.25886f);
	zenith_color_y = (0.00275f*thetas3 - 0.00610f*thetas2 + 0.00317f*thetas) * T2 +
	                 (-0.04214f*thetas3 + 0.08970f*thetas2 - 0.04153f*thetas + 0.00516f) * T +
	                 ( 0.15346f*thetas3 - 0.26756f*thetas2 + 0.06670f*thetas + 0.26688f);
}

// Compute CIE x and y color components
inline void Skylight::computeZenithVenusColor()
{
	static float thetas2;
	static float thetas3;
	static float T2;

	thetas2 = thetas * thetas;
	thetas3 = thetas2 * thetas;
	T2 = T * T;

	zenith_color_x = (0.00166f*thetas3 - 0.00375f*thetas2 + 0.00209f*thetas) * T2 +
	                 (-0.02903f*thetas3 + 0.06377f*thetas2 - 0.03202f*thetas + 0.00394f) * T +
	                 ( 0.11693f*thetas3 - 0.21196f*thetas2 + 0.06052f*thetas + 0.47f);
	zenith_color_y = (0.00275f*thetas3 - 0.00610f*thetas2 + 0.00317f*thetas) * T2 +
	                 (-0.04214f*thetas3 + 0.08970f*thetas2 - 0.04153f*thetas + 0.00516f) * T +
	                 ( 0.15346f*thetas3 - 0.26756f*thetas2 + 0.06670f*thetas + 0.43f);
}

// Compute CIE x and y color components
inline void Skylight::computeZenithMarsColor()
{
	static float thetas2;
	static float thetas3;
	static float T2;

	thetas2 = thetas * thetas;
	thetas3 = thetas2 * thetas;
	T2 = T * T;
	zenith_color_x = (0.00166f*thetas3 - 0.00375f*thetas2 + 0.00209f*thetas) * T2 +
	                 (-0.02903f*thetas3 + 0.06377f*thetas2 - 0.03202f*thetas + 0.00394f) * T +
	                 ( 0.11693f*thetas3 - 0.21196f*thetas2 + 0.06052f*thetas + 0.46f);
	zenith_color_y = (0.00275f*thetas3 - 0.00610f*thetas2 + 0.00317f*thetas) * T2 +
	                 (-0.04214f*thetas3 + 0.08970f*thetas2 - 0.04153f*thetas + 0.00516f) * T +
	                 ( 0.15346f*thetas3 - 0.26756f*thetas2 + 0.06670f*thetas + 0.41f);
}

// Compute the luminance distribution coefficients
inline void Skylight::computeLuminanceDistributionCoefs(void)
{
	AY = 0.1787f*T - 1.4630f;
	BY =-0.3554f*T + 0.4275f;
	CY =-0.0227f*T + 5.3251f;
	DY = 0.1206f*T - 2.5771f;
	EY =-0.0670f*T + 0.3703f;
}

// Compute the color distribution coefficients
inline void Skylight::computeColorDistributionCoefs(void)
{
	Ax =-0.0193f*T - 0.2592f;
	Bx =-0.0665f*T + 0.0008f;
	Cx =-0.0004f*T + 0.2125f;
	Dx =-0.0641f*T - 0.8989f;
	Ex =-0.0033f*T + 0.0452f;

	Ay =-0.0167f*T - 0.2608f;
	By =-0.0950f*T + 0.0092f;
	Cy =-0.0079f*T + 0.2102f;
	Dy =-0.0441f*T - 1.6537f;
	Ey =-0.0109f*T + 0.0529f;
}

// Compute the sky color at the given position in the CIE color system and store it in p.color
// p.color[0] is CIE x color component
// p.color[1] is CIE y color component
// p.color[2] is CIE Y color component (luminance)
void Skylight::get_xyY_Value(skylight_struct * p)
{
	float cos_dist_sun = cosf(p->dist_sun);
	float one_over_cos_zenith_angle = 1.f/cosf(p->zenith_angle);
	p->color[0] = term_x * (1.f + Ax * expf(Bx * one_over_cos_zenith_angle)) * (1.f + Cx * expf(Dx*p->dist_sun) +
	              Ex * cos_dist_sun * cos_dist_sun);
	p->color[1] = term_y * (1.f + Ay * expf(By * one_over_cos_zenith_angle)) * (1.f + Cy * expf(Dy*p->dist_sun) +
	              Ey * cos_dist_sun * cos_dist_sun);
	p->color[2] = term_Y * (1.f + AY * expf(BY * one_over_cos_zenith_angle)) * (1.f + CY * expf(DY*p->dist_sun) +
	              EY * cos_dist_sun * cos_dist_sun);
}

// Compute the sky color at the given position in the CIE color system and store it in p.color
// p.color[0] is CIE x color component
// p.color[1] is CIE y color component
// p.color[2] is CIE Y color component (luminance)

// Digitalis - grabbed from svn for atm hex artifact fix 20070215
void Skylight::get_xyY_Valuev(skylight_struct2& p) const
{
	float cos_dist_sun = sun_pos[0]*p.pos[0]
	                     + sun_pos[1]*p.pos[1]
	                     + sun_pos[2]*p.pos[2];
	float dist_sun;
	if (cos_dist_sun <= -1.f ) {
		cos_dist_sun = -1.f;
		dist_sun = M_PI;
	} else if (cos_dist_sun >= 1.f ) {
		cos_dist_sun = 1.f;
		dist_sun = 0.f;
	} else dist_sun = std::acos(cos_dist_sun);
	const float cos_dist_sun_q = cos_dist_sun*cos_dist_sun;

	float Fx = 0.f;
	float Fy = 0.f;
	float FY = 0.f;

	if (p.pos[2] > 0.f) {
		float one_over_cos_zenith_angle = 1.f / p.pos[2];
		Fx = std::exp(Bx*one_over_cos_zenith_angle);
		Fy = std::exp(By*one_over_cos_zenith_angle);
		FY = std::exp(BY*one_over_cos_zenith_angle);
	}

	p.color[0] = term_x * (1.f + Ax * Fx)
	             * (1.f + Cx * std::exp(Dx*dist_sun) + Ex * cos_dist_sun_q);

	p.color[1] = term_y * (1.f + Ay * Fy)
	             * (1.f + Cy * std::exp(Dy*dist_sun) + Ey * cos_dist_sun_q);

	p.color[2] = term_Y * (1.f + AY * FY)
	             * (1.f + CY * std::exp(DY*dist_sun) + EY * cos_dist_sun_q);


	if (p.color[2] < 0 || p.color[0] < 0 || p.color[1] < 0) {
		p.color[0] = 0.25;
		p.color[1] = 0.25;
		p.color[2] = 0;
	}
}

// Return the current zenith color in xyY color system
void Skylight::getZenithColor(float * v) const
{
	v[0] = zenith_color_x;
	v[1] = zenith_color_y;
	v[2] = zenith_luminance;
}
