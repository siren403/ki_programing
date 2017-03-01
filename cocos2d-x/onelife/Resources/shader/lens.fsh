#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

uniform vec2 u_resolution;

void main()
{

    vec3 color = vec3(1.0,1.0,1.0);

    //border
    vec2 oriuv;
    #ifdef GL_ES
    oriuv = gl_FragCoord.xy / u_resolution.xy*1.-1.;
    #else
    oriuv = gl_FragCoord.xy / u_resolution.xy*2.-1.;
    #endif
    // vec2 oriuv = gl_FragCoord.xy;//-1~1
    color = mix(vec3(0.),color,pow(max(0.,.95-length(oriuv*oriuv*oriuv*vec2(1.05,1.1))),.3));

    gl_FragColor = vec4(color, 1.0);

}
