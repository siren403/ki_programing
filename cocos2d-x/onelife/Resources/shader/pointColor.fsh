#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

uniform vec3 pointColor;
uniform vec3 changeColor;
uniform float colorRatio;

void main()
{
    vec4 color = texture2D(CC_Texture0, v_texCoord);

    if(color.rgb == pointColor)
    {
        // color = v_fragmentColor.rgb;
        // color += addColor;
        color.rgb = changeColor * colorRatio;
    }

    gl_FragColor = color * v_fragmentColor;
}
