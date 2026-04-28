#include <flustral/rendering/effects/native/native_shaders.hpp>




const char* const NativeShaders::HorizontalBlurShader = R"(
#version 330


uniform vec2 u_resolution;
uniform int u_samples;
uniform float u_sigma;

uniform sampler2D u_texture;


out vec4 out_color;


void main()
{
   	vec2 uv = gl_FragCoord.xy / u_resolution;

    vec4 result = vec4(0.0);
    float total = 0.0;

    for (int i = -u_samples; i <= u_samples; i++)
    {
        float w = exp(-float(i * i) / (2.0 * u_sigma * u_sigma));
        result += texture(u_texture, uv + vec2(float(i) / u_resolution.x, 0.0)) * w;
        total += w;
    }

    out_color = result / total;
}
)";




const char* const NativeShaders::VerticalBlurShader = R"(
#version 330


uniform vec2 u_resolution;
uniform int u_samples;
uniform float u_sigma;

uniform sampler2D u_texture;


out vec4 out_color;


void main()
{
   	vec2 uv = gl_FragCoord.xy / u_resolution;

    vec4 result = vec4(0.0);
    float total = 0.0;

    for (int i = -u_samples; i <= u_samples; i++)
    {
        float w = exp(-float(i * i) / (2.0 * u_sigma * u_sigma));
        result += texture(u_texture, uv + vec2(0.0, float(i) / u_resolution.y)) * w;
        total += w;
    }

    out_color = result / total;
}
)";




const char* const NativeShaders::DistortionShader = R"(
#version 330

uniform vec2 u_resolution;
uniform vec2 u_position;

uniform vec2 u_size;
uniform float u_radius;
uniform float u_border_width;
uniform float u_ior;
uniform float u_strength;
uniform float u_lens_strength;
uniform float u_noise_strength;

uniform float u_chromatic_green;
uniform float u_chromatic_blue;

uniform float u_fresnel_power;
uniform float u_fresnel_strength;

uniform vec3 u_tint;
uniform float u_tint_strength;

uniform sampler2D u_background;
uniform sampler2D u_blurred_background;

out vec4 outColor;


// vec2 roundedBoxSize()
// {
//     return u_size / u_resolution * vec2(u_resolution.x / u_resolution.y, 1.0);
// }

float sdRoundedBox(vec2 p, vec2 b, float r)
{
    vec2 q = abs(p) - b + r;
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;
}

vec2 sdfNormal(vec2 p, float eps)
{
    vec2 b = u_size * 0.5;
    return normalize(vec2(
        sdRoundedBox(p + vec2(eps, 0.0), b, u_radius) - sdRoundedBox(p - vec2(eps, 0.0), b, u_radius),
        sdRoundedBox(p + vec2(0.0, eps), b, u_radius) - sdRoundedBox(p - vec2(0.0, eps), b, u_radius)
    ));
}

vec2 snellRefraction(vec2 n2d, float eta)
{
    vec3 n3        = normalize(vec3(n2d, sqrt(max(0.0, 1.0 - dot(n2d, n2d)))));
    vec3 incident  = vec3(0.0, 0.0, -1.0);
    vec3 refracted = refract(incident, n3, eta);
    return refracted.xy;
}

float fresnelSchlick(vec2 normal, float power)
{
    float cosTheta = clamp(1.0 - length(normal), 0.0, 1.0);
    return pow(1.0 - cosTheta, power);
}


float hash(vec2 p)
{
    return fract(sin(dot(p, vec2(12.9898,78.233))) * 43758.5453);
}


void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution;
    float aspect = u_resolution.x / u_resolution.y;

    vec2 p = (uv - u_position) * u_resolution;
    vec2 half_size = u_size * 0.5;
    float sdf = sdRoundedBox(p, half_size, u_radius);

    vec2 sdfN  = sdfNormal(p, 0.001);
    sdfN.y *= -1; // you're inverting the y axis below, so inverting the y from the normal is also needed

    vec2 lensN = p / (half_size + u_radius);

    float borderBlend  = 1.0 - smoothstep(0.0, u_border_width, abs(sdf));
    float inside       = smoothstep(0.0015, -0.0015, sdf);

    float eta          = 1.0 / u_ior;

    vec2 blendedNormal = mix(lensN * u_lens_strength, sdfN, borderBlend);

    vec2 totalOffset   = snellRefraction(blendedNormal, eta) * inside * u_strength;


    float n1 = hash(gl_FragCoord.xy);
    float n2 = hash(gl_FragCoord.xy + 19.19);

    vec2 jitter = vec2(n1, n2) - 0.5;

    jitter *= u_noise_strength / u_resolution;
    uv += jitter * inside;


    vec2 blur_uv = uv;
    blur_uv.y = 1.0 - blur_uv.y;

    vec4 blurred = vec4(
        texture(u_blurred_background, blur_uv + totalOffset).r,
        texture(u_blurred_background, blur_uv + totalOffset * u_chromatic_green).g,
        texture(u_blurred_background, blur_uv + totalOffset * u_chromatic_blue).b,
        1.0
    );

    float fresnelVal = fresnelSchlick(sdfN * borderBlend, u_fresnel_power);

    vec4 original = texture(u_background, uv);

    vec3 glassColor = blurred.rgb;
    glassColor += fresnelVal * u_fresnel_strength;
    glassColor  = mix(glassColor, glassColor * u_tint, inside * u_tint_strength);

    outColor = mix(original, vec4(glassColor, 1.0), inside);
}
)";




const char* const NativeShaders::BlurMaskShader = R"(
#version 330

uniform vec2 u_position;
uniform vec2 u_size;
uniform float u_radius;
uniform float u_noise_strength;

uniform vec2 u_resolution;
uniform sampler2D u_background;
uniform sampler2D u_blurred_background;

out vec4 out_color;

float sdRoundedBox(vec2 p, vec2 b, float r)
{
    vec2 q = abs(p) - b + r;
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;
}


float hash(vec2 p)
{
    return fract(sin(dot(p, vec2(12.9898,78.233))) * 43758.5453);
}


void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution;

    vec2 p = (uv - u_position) * u_resolution;
    vec2 half_size = u_size * 0.5;

    float sdf = sdRoundedBox(p, half_size, u_radius);

    float inside = smoothstep(0.0015, -0.0015, sdf);

    float n1 = hash(gl_FragCoord.xy);
    float n2 = hash(gl_FragCoord.xy + 19.19);

    vec2 jitter = vec2(n1, n2) - 0.5;

    jitter *= u_noise_strength / u_resolution;
    uv += jitter * inside;


    vec2 blur_uv = uv;
    blur_uv.y = 1.0 - blur_uv.y;

    vec4 blurred = vec4(
        texture(u_blurred_background, blur_uv).r,
        texture(u_blurred_background, blur_uv).g,
        texture(u_blurred_background, blur_uv).b,
        1.0
    );

    vec4 original = texture(u_background, uv);

    out_color = mix(original, blurred, inside);
}
)";