//
// body ringed
//
#version 420
#pragma debug(on)
#pragma optimize(off)

layout (binding=4) uniform sampler2D mapTexture;
layout (binding=5) uniform sampler2D shadowTexture;
layout (binding=6) uniform sampler2D ringTexture;

layout (binding=1) uniform globalFrag {
	vec3 MoonPosition1;
	float MoonRadius1;
	vec3 MoonPosition2;
	float MoonRadius2;
	vec3 MoonPosition3;
	float MoonRadius3;
	vec3 MoonPosition4;
	float MoonRadius4;
	float SunHalfAngle;
};

layout (binding=3) uniform ringFrag {
	uniform float RingInnerRadius;
	uniform float RingOuterRadius;
};

layout (location=0) in vec2 TexCoord;
layout (location=1) in float Ambient;
layout (location=2) in vec3 Position;
layout (location=3) in float NdotL;
layout (location=4) in vec3 Light; 
layout (location=5) in vec3 ModelLight;
layout (location=6) in vec3 OriginalPosition;

layout (location=0) out vec4 FragColor;

void main(void)
{ 
	float diffuse = max(NdotL, 0.0);
	vec3 color = vec3(texture(mapTexture, TexCoord)).rgb;
	// FragColor = vec4(color, 1.0);
	if(diffuse != 0.0) {
		if(RingOuterRadius != 0.0) {
			vec3 intersect = ModelLight;
			float scale = (-1.0 * OriginalPosition.z/intersect.z); 
			intersect = intersect*scale  + OriginalPosition; 
			if(dot(intersect,ModelLight) >= 0.0) {
				float radius = length(intersect); 
				if(radius < RingOuterRadius && radius > RingInnerRadius ) {	
					vec2 coord = vec2(1.0-(radius-RingInnerRadius)/(RingOuterRadius-RingInnerRadius), 1.0);	
	                vec4 rcolor = vec4(texture(ringTexture, coord)); 
					diffuse = diffuse*mix(1.0, 0.3, rcolor.a); 
				}
			}
		}                     
		vec3 moon; 
		float moonHalfAngle;
		vec2 ratio; 
		float distance;
		vec3 lookup;
		if(MoonRadius1 != 0.0) { 
			moon = MoonPosition1 - Position;
			moonHalfAngle = atan( MoonRadius1/ length(moon) ); 
			distance = acos(dot(Light, normalize(moon))); 
			ratio.y = clamp(moonHalfAngle/SunHalfAngle/51.2, 0.0, 1.0); 
			ratio.x = distance/(moonHalfAngle + SunHalfAngle); 
			lookup = vec3(texture(shadowTexture, ratio)).rgb; 
			diffuse = diffuse * lookup.r; 
		} 
		if(MoonRadius2 != 0.0) { 
			moon = MoonPosition2 - Position;
			moonHalfAngle = atan( MoonRadius2/ length(moon) ); 
			distance = acos(dot(Light, normalize(moon))); 
			ratio.y = clamp(moonHalfAngle/SunHalfAngle/51.2, 0.0, 1.0); 
			ratio.x = distance/(moonHalfAngle + SunHalfAngle); 
			lookup = vec3(texture(shadowTexture, ratio)).rgb; 
			diffuse = diffuse * lookup.r; 
		} 
		if(MoonRadius3 != 0.0) { 
			moon = MoonPosition3 - Position;
			moonHalfAngle = atan( MoonRadius3/ length(moon) ); 
			distance = acos(dot(Light, normalize(moon))); 
			ratio.y = clamp(moonHalfAngle/SunHalfAngle/51.2, 0.0, 1.0); 
			ratio.x = distance/(moonHalfAngle + SunHalfAngle); 
			lookup = vec3(texture(shadowTexture, ratio)).rbg; 
			diffuse = diffuse * lookup.r; 
		} 
		if(MoonRadius4 != 0.0) { 
			moon = MoonPosition4 - Position;
			moonHalfAngle = atan( MoonRadius4/ length(moon) ); 
			distance = acos(dot(Light, normalize(moon))); 
			ratio.y = clamp(moonHalfAngle/SunHalfAngle/51.2, 0.0, 1.0); 
			ratio.x = distance/(moonHalfAngle + SunHalfAngle); 
			lookup = vec3(texture(shadowTexture, ratio)).rgb; 
			diffuse = diffuse * lookup.r; 
		} 
	}
	FragColor = vec4(color*(min(diffuse+Ambient, 1.0)), 1.0);
} 



//~ uniform sampler2D mapTexture;                                  
//~ uniform sampler2D RingTexture;								
//~ uniform float RingInnerRadius;								
//~ uniform float RingOuterRadius;								
//~ uniform sampler2D shadowTexture;							
//~ uniform float SunHalfAngle;									
//~ uniform vec3 MoonPosition1;									
//~ uniform float MoonRadius1;									
//~ uniform vec3 MoonPosition2;									
//~ uniform float MoonRadius2;									
//~ uniform vec3 MoonPosition3;									
//~ uniform float MoonRadius3;									
//~ uniform vec3 MoonPosition4;									
//~ uniform float MoonRadius4;									
//~ varying vec2 TexCoord;										
//~ uniform float Ambient;  									
//~ varying vec3 Position;                                      
//~ varying vec3 OriginalPosition;								
//~ varying float NdotL;										
//~ varying vec3 Light;											
//~ varying vec3 ModelLight;
									
//~ void main(void)												
//~ {															
	//~ float diffuse = max(NdotL, 0.0);						
	//~ vec3 color = vec3(texture(mapTexture, TexCoord));		
	//~ if(diffuse != 0.0) {									
		//~ if(RingOuterRadius != 0.0) {						
			//~ vec3 intersect = ModelLight;					
			//~ float scale = (-1.0 * OriginalPosition.z/intersect.z); 
			//~ intersect = intersect*scale  + OriginalPosition; 
			//~ if(dot(intersect,ModelLight) >= 0.0) {			 
				//~ float radius = length(intersect);			 
				//~ if(radius < RingOuterRadius && radius > RingInnerRadius ) {	
					//~ vec2 coord = vec2(1.0-(radius-RingInnerRadius)/(RingOuterRadius-RingInnerRadius), 1.0);	
	                //~ vec4 rcolor = vec4(texture(RingTexture, coord)); 
					//~ diffuse = diffuse*mix(1.0, 0.3, rcolor.a); 
				//~ }											
			//~ }												
		//~ }                                                   
		//~ vec3 moon;											
		//~ float moonHalfAngle;								
		//~ vec2 ratio;											
		//~ float distance;										
		//~ vec3 lookup;										
		//~ if(MoonRadius1 != 0.0) {							
			//~ moon = MoonPosition1 - Position;				
			//~ moonHalfAngle = atan( MoonRadius1/ length(moon) ); 
			//~ distance = acos(dot(Light, normalize(moon)));	
			//~ ratio.y = clamp(moonHalfAngle/SunHalfAngle/51.2, 0.0, 1.0); 
			//~ ratio.x = distance/(moonHalfAngle + SunHalfAngle); 
			//~ lookup = vec3(texture(shadowTexture, ratio)); 
			//~ diffuse = diffuse * lookup.r;					
		//~ }													
		//~ if(MoonRadius2 != 0.0) {							
			//~ moon = MoonPosition2 - Position;				
			//~ moonHalfAngle = atan( MoonRadius2/ length(moon) ); 
			//~ distance = acos(dot(Light, normalize(moon)));	
			//~ ratio.y = clamp(moonHalfAngle/SunHalfAngle/51.2, 0.0, 1.0); 
			//~ ratio.x = distance/(moonHalfAngle + SunHalfAngle); 
			//~ lookup = vec3(texture(shadowTexture, ratio)); 
			//~ diffuse = diffuse * lookup.r;					
		//~ }													
		//~ if(MoonRadius3 != 0.0) {							
			//~ moon = MoonPosition3 - Position;				
			//~ moonHalfAngle = atan( MoonRadius3/ length(moon) ); 
			//~ distance = acos(dot(Light, normalize(moon)));	
			//~ ratio.y = clamp(moonHalfAngle/SunHalfAngle/51.2, 0.0, 1.0); 
			//~ ratio.x = distance/(moonHalfAngle + SunHalfAngle); 
			//~ lookup = vec3(texture(shadowTexture, ratio)); 
			//~ diffuse = diffuse * lookup.r;					
		//~ }													
		//~ if(MoonRadius4 != 0.0) {							
			//~ moon = MoonPosition4 - Position;				
			//~ moonHalfAngle = atan( MoonRadius4/ length(moon) ); 
			//~ distance = acos(dot(Light, normalize(moon)));	
			//~ ratio.y = clamp(moonHalfAngle/SunHalfAngle/51.2, 0.0, 1.0); 
			//~ ratio.x = distance/(moonHalfAngle + SunHalfAngle); 
			//~ lookup = vec3(texture(shadowTexture, ratio)); 
			//~ diffuse = diffuse * lookup.r;					
		//~ }													
	//~ }														
	//~ gl_FragColor = vec4(color*(min(diffuse+Ambient, 1.0)), 1.0);		
//~ }															

 
