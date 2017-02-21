#ifdef GL_ES
precision mediump float;
#endif

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif


const float PI = 3.14;

void main( void ) {

	// vec2 position = (2.0*gl_FragCoord.xy - resolution.xy)/resolution.x;
    vec2 position = v_texCoord;
	float intensity = 0.01/abs(length(position) - .32);
	vec3 color = vec3(intensity*.2, 0, intensity);

	// for(float i = .0; i < 5.; i++) {
	// 	vec2 q = position.xy + 0.2*vec2(cos(i*2.*PI/5. + time), sin(i*2.*PI/5. + time));
	// 	float intensity = .01/abs(length(q) - (.1*abs(sin(time)) + .1));
	// 	color += vec3(0, intensity, intensity*0.5);
	// }

	gl_FragColor = vec4(vec3(color), 1.0);

}
