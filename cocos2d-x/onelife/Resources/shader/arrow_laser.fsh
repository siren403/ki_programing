#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

uniform float u_laserFactor;

void main()
{
    vec2 uv = v_texCoord;
    vec4 color = texture2D(CC_Texture0, uv);

    if (color.a > u_laserFactor)
    {
        color = vec4(1.0, 1.0, 1.0, color.a);
    }
    else
    {
        color = color * v_fragmentColor;
    }
    gl_FragColor = color;
}
