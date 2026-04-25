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

)";