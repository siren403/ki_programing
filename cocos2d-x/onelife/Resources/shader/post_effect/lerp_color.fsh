#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

uniform vec3 u_lerpColor;
uniform float u_blend;
uniform vec2 u_resolution;
uniform float u_outLineThickness;
uniform vec4 u_outLineColor;

void main()
{
    vec2 texCoord = v_texCoord;
    texCoord.xy = texCoord.xy * atan(3.14159 * texCoord.x);
    vec4 tex = texture2D(CC_Texture0,texCoord);

    // vec3 col = u_lerpColor;
    // vec3 col = vec3(tex.r * 0.3, tex.g*0.59, tex.b * 0.11);
    float val = tex.r * 0.3 + tex.g*0.59 + tex.b * 0.11;
    vec3 col = vec3(val,val,val);
    // vec3 col = tex.rgb * u_lerpColor.rgb;
    tex.rgb = mix(tex.rgb,col.rgb,u_blend);

    vec2 outLine;

    outLine.x = u_outLineThickness / u_resolution.x;
    outLine.y = u_outLineThickness / u_resolution.y;

    if(v_texCoord.x < outLine.x || v_texCoord.x > 1 - outLine.x||
        v_texCoord.y < outLine.y || v_texCoord.y > 1 - outLine.y)
    {
        // tex.rgb = vec3(1.0,0.0,0.0);
        tex = u_outLineColor;
    }


    gl_FragColor = tex;

    // gl_FragColor = texture2D(CC_Texture0,v_texCoord);
}
