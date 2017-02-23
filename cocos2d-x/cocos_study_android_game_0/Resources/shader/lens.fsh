#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_lensSize; // 0.4
uniform vec3 u_lensColor;
uniform float u_outLine;
uniform float u_inLine;
#define EPSILON 0.000011
#define PI 3.14159

void main()
{

    vec2 m = u_mouse.xy / u_resolution.xy;

    vec2 d = v_texCoord - m;
    float r = sqrt(dot(d, d)); // distance of pixel from mouse

    vec2 uv;
    vec3 color = vec3(1.0, 0.0, 0.0);

    if (r > u_lensSize+u_outLine)//outline
    {
        uv = v_texCoord;
        color = texture2D(CC_Texture0, uv).xyz;
    }
    else if (r < u_lensSize-u_inLine)//inline
    {
        // Thanks to Paul Bourke for these formulas; see
        // http://paulbourke.net/miscellaneous/lenscorrection/
        // and .../lenscorrection/lens.c
        // Choose one formula to uncomment:
        // SQUAREXY:
        // uv = m + vec2(d.x * abs(d.x), d.y * abs(d.y));
        // SQUARER:
        //uv = m + d * r; // a.k.a. m + normalize(d) * r * r
        // SINER:
        // uv = m + normalize(d) * sin(r * PI * 0.5);
        // ASINR:
        uv = m + normalize(d) * asin(r) / (PI * 0.5);
        // Nothing
        //uv = v_texCoord;
        color = texture2D(CC_Texture0, vec2(uv.x, uv.y)).xyz;
        color *= u_lensColor;

        uv.x += -(m.x - 0.5);
        uv.y += -(m.y - 0.5);
    }
    //border
    vec2 oriuv = gl_FragCoord.xy / u_resolution.xy*2.-1.;
    // vec2 oriuv = gl_FragCoord.xy;//-1~1
    color=mix(vec3(0.),color,pow(max(0.,.95-length(oriuv*oriuv*oriuv*vec2(1.05,1.1))),.3));

    gl_FragColor = vec4(color, 1.0);
}
