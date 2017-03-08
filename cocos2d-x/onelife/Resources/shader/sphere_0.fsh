#ifdef GL_ES
precision mediump float;
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

#define particles_count 0.2
#define k 0.2

#define zmul(a, b) vec2(a.x*b.x-a.y*b.y, a.x*b.y+b.x*a.y)
#define zinv(a) vec2(a.x, -a.y) / dot(a,a*(0.7 + 0.6*sin(time)))

void main()
{

    vec2 g = gl_FragCoord.xy;
	vec2 si = vec2(256.,256.);
    vec2 m = vec2(128.,128.)/si;
	float t = time;
    vec3 stars = vec3(0);

    vec2 z = (g+g-si)/min(si.x,si.y) * 2.;

	vec2 c = vec2(0.96,1.23);

   	float r = 0.;
	for (float i=0.;i<2.;i++)
	{
		if (r > 4.) break;
        r = dot(z,z);
		z = zinv( (zmul(z, z) + c));

        vec3 col = mix(vec3(0.5,0,0.5), vec3(-3.*sin(0.7*time),4. * cos(0.6*time),-3.29), i/(12.*(0.8 + 0.5*sin(0.4*time))));

        vec3 acc = vec3(0);
		for (float j=0.;j<particles_count;j++)
		{
		    float tt = t + j/(3.14159/(particles_count*k));
		    vec2 b = vec2(cos(tt), sin(tt)) * 2.;
			acc += col/r/8./dot(z-b,z-b);
		}
        stars += acc / particles_count / 0.75;
    }

    gl_FragColor = vec4(stars * 0.3,1);
}
