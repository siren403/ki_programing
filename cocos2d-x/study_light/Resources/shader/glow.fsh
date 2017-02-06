varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform float u_ctime;
uniform float u_threshold;
uniform float u_radius;
uniform vec4  u_outlineColor;

void main() {
    float radius = u_radius;

    vec4 accum  = vec4(0.0);
    vec4 normal = vec4(0.0);

    normal = texture2D(CC_Texture0, v_texCoord);

    for(float i = 1.0; i <= radius; i += 1.0) {
        accum += texture2D(CC_Texture0, vec2(v_texCoord.x - 0.01 * i, v_texCoord.y - 0.01 * i));
        accum += texture2D(CC_Texture0, vec2(v_texCoord.x + 0.01 * i, v_texCoord.y - 0.01 * i));
        accum += texture2D(CC_Texture0, vec2(v_texCoord.x + 0.01 * i, v_texCoord.y + 0.01 * i));
        accum += texture2D(CC_Texture0, vec2(v_texCoord.x - 0.01 * i, v_texCoord.y + 0.01 * i));
    }

    accum.rgb =  u_outlineColor.rgb * u_outlineColor.a * accum.a * 0.95;
    float opacity = ((1.0 - normal.a) / radius) * (u_ctime / u_threshold);

    normal = (accum * opacity) + (normal * normal.a);

    gl_FragColor = v_fragmentColor * normal;

    // vec4 normal = texture2D(CC_Texture0, v_texCoord);
    //
    // if(normal.a == 0)
    // {
    //     normal.r = 1.0;
    // }
    //
    // gl_FragColor = v_fragmentColor * normal;
}
