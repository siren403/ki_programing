#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;

uniform vec2 u_stepSize;

void main()
{
    vec4 color = texture(CC_Texture0,v_texCoord);
    vec4 result = vec4(0.0,0.0,0.0,0.0);
    vec2 r_stepSize = vec2(u_stepSize.x, -u_stepSize.y);

    result += texture2D(CC_Texture0, v_texCoord -  -4.0 * u_stepSize) * 0.05;
    result += texture2D(CC_Texture0, v_texCoord -  -3.0 * u_stepSize) * 0.09;
    result += texture2D(CC_Texture0, v_texCoord -  -2.0 * u_stepSize) * 0.12;
    result += texture2D(CC_Texture0, v_texCoord -  -1.0 * u_stepSize) * 0.15;
    result += texture2D(CC_Texture0, v_texCoord -  0.0 * u_stepSize) * 0.16;
    result += texture2D(CC_Texture0, v_texCoord -  1.0 * u_stepSize) * 0.15;
    result += texture2D(CC_Texture0, v_texCoord -  2.0 * u_stepSize) * 0.12;
    result += texture2D(CC_Texture0, v_texCoord -  3.0 * u_stepSize) * 0.09;
    result += texture2D(CC_Texture0, v_texCoord -  4.0 * u_stepSize) * 0.05;

    result += texture2D(CC_Texture0, v_texCoord -  -4.0 * r_stepSize) * 0.05;
    result += texture2D(CC_Texture0, v_texCoord -  -3.0 * r_stepSize) * 0.09;
    result += texture2D(CC_Texture0, v_texCoord -  -2.0 * r_stepSize) * 0.12;
    result += texture2D(CC_Texture0, v_texCoord -  -1.0 * r_stepSize) * 0.15;
    result += texture2D(CC_Texture0, v_texCoord -  0.0 * r_stepSize) * 0.16;
    result += texture2D(CC_Texture0, v_texCoord -  1.0 * r_stepSize) * 0.15;
    result += texture2D(CC_Texture0, v_texCoord -  2.0 * r_stepSize) * 0.12;
    result += texture2D(CC_Texture0, v_texCoord -  3.0 * r_stepSize) * 0.09;
    result += texture2D(CC_Texture0, v_texCoord -  4.0 * r_stepSize) * 0.05;

    result /= 3.0;
    if(color.a >= 1.0)
    {
        result = color;
    }
    else if(result.a > 0.0)
    {
        result.rgb = vec3(result.a,result.a,result.a);
    }

    gl_FragColor = result;
}
