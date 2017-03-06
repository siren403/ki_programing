#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

#define START_ANGLE 0.0
#define END_ANGLE 0.75

#define RADIUS 0.5
#define PI 3.14159 * 2

void main()
{
    vec2 center = vec2(0.5,0.5);
    vec2 dir = v_texCoord - center;
    float r = sqrt(dot(dir,dir));
    float deg = atan(dir.y,dir.x);

    vec4 color = vec4(0,1,0,1);

    float size = RADIUS * 1;
    if( (r < size && r > size - size * 0.1)
        && (START_ANGLE * PI <= deg && END_ANGLE * PI >= deg))
    {
        color = v_fragmentColor;
    }

    gl_FragColor = color;
}
