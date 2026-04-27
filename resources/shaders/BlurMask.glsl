#version 330

uniform vec2 u_position;
uniform vec2 u_size;
uniform float u_radius;
uniform float u_noise_strength;

uniform vec2 u_resolution;
uniform sampler2D u_background;
uniform sampler2D u_blurred_background;

out vec4 out_color;


vec2 roundedBoxSize()
{
    return u_size / u_resolution * vec2(u_resolution.x / u_resolution.y, 1.0);
}

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
    float aspect = u_resolution.x / u_resolution.y;

    vec2 p = (uv - u_position) * vec2(aspect, 1.0);
    float sdf = sdRoundedBox(p, roundedBoxSize(), u_radius);

    float inside = smoothstep(0.0015, -0.0015, sdf);

    float n1 = hash(gl_FragCoord.xy);
    float n2 = hash(gl_FragCoord.xy + 19.19);

    vec2 jitter = vec2(n1, n2) - 0.5;

    jitter *= u_noise_strength / u_resolution;
    uv += jitter * inside;


    vec4 blurred = vec4(
        texture(u_blurred_background, uv).r,
        texture(u_blurred_background, uv).g,
        texture(u_blurred_background, uv).b,
        1.0
    );

    vec4 original = texture(u_background, uv);

    out_color = mix(original, blurred, inside);
}
