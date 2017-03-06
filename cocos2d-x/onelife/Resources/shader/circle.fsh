#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

#define RADIUS 0.5

uniform float u_size;
uniform float u_outline;
uniform float u_inline;


void main()
{
    vec2 center = vec2(0.5,0.5);

    vec2 dir = v_texCoord - center;
    float r = sqrt(dot(dir,dir));

    vec4 color = vec4(0,0,0,0);

    float size = RADIUS * u_size;

    if(r < size + size * u_outline
        && r > size - size * u_inline)
    {
        color = v_fragmentColor;
    }


    gl_FragColor = color;
}
