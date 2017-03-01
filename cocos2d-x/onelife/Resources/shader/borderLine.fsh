#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif


void main()
{
    vec2 uv = v_texCoord;

    vec3 color = texture2D(CC_Texture0,uv).rgb;

    if(uv.x <= 0.1 || uv.x >= 0.9 || uv.y <= 0.1 || uv.y >= 0.9)
    {
        color = vec3(1,0,0);
    }

    gl_FragColor = vec4(color,1.0);
}
