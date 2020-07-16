//
// illuminate
//

#version 420
#pragma debug(on)
#pragma optimize(off)

#define M_PI 3.14159265358979323846

//layout
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in Data
{
    vec3 position;
	vec2 texCoord;
    vec3 texColor;
} data[];

out DataFrag
{
	vec2 texCoord;
    vec3 texColor;
} dataFrag;



layout (std140) uniform cam_block
{
	ivec4 viewport;
	ivec4 viewport_center;
	vec4 main_clipping_fov;
	mat4 MVP2D;
	float ambient;
	float time;
};

uniform mat4 ModelViewMatrix;

//////////////////// PROJECTION FISHEYE ////////////////////////////////

double my_atan(double x)
{
    double a, z, p, r, s, q, o;
    /* argument reduction: 
       arctan (-x) = -arctan(x); 
       arctan (1/x) = 1/2 * pi - arctan (x), when x > 0
    */
    z = abs (x);
    a = (z > 1.0) ? 1.0 / z : z;
    /* evaluate minimax polynomial approximation */
    s = a * a; // a**2
    q = s * s; // a**4
    o = q * q; // a**8
    /* use Estrin's scheme for low-order terms */
    p = fma (fma (fma (0.0000202585530444381072727802473032454599888296797871589660644531250, s,0.000223022403457582792975222307774174623773433268070220947265625), q,
                  fma (-0.00116407177799304783517853056906687925220467150211334228515625, s, 0.0038559749383629666162620619473955230205319821834564208984375)), o,
             fma (fma (-0.00918455921871650336762993305228519602678716182708740234375, s, 0.016978035834597275666180138387062470428645610809326171875), q, 
                  fma (-0.02582679681449594200071118166306405328214168548583984375, s,0.034067811082715081238969645482939085923135280609130859375 )));
    /* use Horner's scheme for high-order terms */
    p = fma (fma (fma (fma (fma (fma (fma (fma (fma (fma (fma (fma (p, s,
        -0.040926382420509950510467689355209586210548877716064453125), s,
        0.0467394961991579871440904980772756971418857574462890625), s, 
        -0.052392330054601317368412338737471145577728748321533203125), s,  
        0.058773077721790849270444567764570820145308971405029296875), s, 
        -0.06665860363351257256159243524962221272289752960205078125), s,  
        0.07692212930586783681263796097482554614543914794921875), s,
        -0.090909012354005225287068014949909411370754241943359375), s,
        0.11111110678749423763544967869165702722966670989990234375), s,
        -0.14285714271334815084202318757888861000537872314453125), s,
        0.199999999997550192976092375829466618597507476806640625), s,
        -0.3333333333333186043745399729232303798198699951171875) * s, a, a);
    /* back substitution based on argument reduction */
    r = (z > 1.0) ? (1.5707963267948965579989817342720925807952880859375- p) : p;
	//~ return copysign (r, x);
    if (x>=0) 
		return r;
    else
		return (-r);
}


vec4 custom_project(vec3 invec)
{
	float zNear=main_clipping_fov[0];
	float zFar=main_clipping_fov[1];
	float fov=main_clipping_fov[2];

	float fisheye_scale_factor = 1.0/fov*180.0/M_PI*2.0;
	float viewport_center_x=viewport_center[0];
	float viewport_center_y=viewport_center[1];
	float viewport_radius=viewport_center[2];

    vec4 win = vec4(invec,1.0);
    win=ModelViewMatrix*win;
    win[3]=0.0;
	
	float depth = length(win);

    float rq1 = win.x*win.x+win.y*win.y;

	if (rq1 <= 0.0 ) {
		if (win.z < 0.0) {
			win.x = viewport_center_x;
			win.y = viewport_center_y;
			win.z = 1.0;
			win.w = 0.0;
			return win;
		}
		win.x = viewport_center_x;
		win.y = viewport_center_y;
		win.z = -1e30;
		win.w = 0.0;
		return win;
	}
	else{
        float oneoverh = 1.0/sqrt(rq1);
        //~ float a = M_PI/2.0 + atan(win.z*oneoverh);
        double aa = M_PI/2.0 + my_atan(win.z*oneoverh);
        float a = float(aa);
        
        float f = a * fisheye_scale_factor;

        f *= viewport_radius * oneoverh;

        win.x = viewport_center_x + win.x * f;
        win.y = viewport_center_y + win.y * f;

        win.z = (abs(depth) - zNear) / (zFar-zNear);

        if (a<0.9*M_PI)
			win.w=1.0;
		else
			win.w=0.0;
        return win;
	}
}

//////////////////// PROJECTION FISHEYE ////////////////////////////////


void main(void)
{
	vec4 pos1, pos2, pos3;
	pos1 = custom_project(data[0].position);
	pos2 = custom_project(data[1].position);
	pos3 = custom_project(data[2].position);

	if ( pos1.w==1.0 && pos2.w==1.0 && pos3.w==1.0) {

		gl_Position = MVP2D * pos1;
		dataFrag.texCoord = data[0].texCoord;
        dataFrag.texColor = data[0].texColor;
		EmitVertex();

		gl_Position = MVP2D * pos2;
		dataFrag.texCoord = data[1].texCoord;
		dataFrag.texColor = data[1].texColor;
		EmitVertex();

		gl_Position = MVP2D * pos3;
		dataFrag.texCoord = data[2].texCoord;
		dataFrag.texColor = data[2].texColor;
		EmitVertex();

		EndPrimitive();	
	}
}