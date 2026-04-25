#version 330

uniform vec2 uResolution;
uniform vec2 uMousePosition;

uniform vec2 uSize;
uniform float uRadius;
uniform float uBorderWidth;
uniform float uIOR;
uniform float uStrength;
uniform float uLensStrength;
uniform float uNoiseStrength;

uniform float uChromaticGreen;
uniform float uChromaticBlue;

uniform float uFresnelPower;
uniform float uFresnelStrength;

uniform vec3 uTint;
uniform float uTintStrength;

uniform sampler2D Background;
uniform sampler2D VerticalBlurRT;

out vec4 outColor;


vec2 roundedBoxSize()
{
    return uSize / uResolution * vec2(uResolution.x / uResolution.y, 1.0);
}

float sdRoundedBox(vec2 p, vec2 b, float r)
{
    vec2 q = abs(p) - b + r;
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;
}

vec2 sdfNormal(vec2 p, float eps)
{
    vec2 b = roundedBoxSize();
    return normalize(vec2(
        sdRoundedBox(p + vec2(eps, 0.0), b, uRadius) - sdRoundedBox(p - vec2(eps, 0.0), b, uRadius),
        sdRoundedBox(p + vec2(0.0, eps), b, uRadius) - sdRoundedBox(p - vec2(0.0, eps), b, uRadius)
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
    vec2 uv = gl_FragCoord.xy / uResolution;
    float aspect = uResolution.x / uResolution.y;

    vec2 p = (uv - uMousePosition) * vec2(aspect, 1.0);
    float sdf = sdRoundedBox(p, roundedBoxSize(), uRadius);

    vec2 sdfN  = sdfNormal(p, 0.001);
    vec2 lensN = p / (roundedBoxSize() + uRadius);

    float borderBlend  = 1.0 - smoothstep(0.0, uBorderWidth, abs(sdf));
    float inside       = smoothstep(0.0015, -0.0015, sdf);

    float eta          = 1.0 / uIOR;

    vec2 blendedNormal = mix(lensN * uLensStrength, sdfN, borderBlend);

    vec2 totalOffset   = snellRefraction(blendedNormal, eta) * inside * uStrength;


    float n1 = hash(gl_FragCoord.xy);
    float n2 = hash(gl_FragCoord.xy + 19.19);

    vec2 jitter = vec2(n1, n2) - 0.5;

    jitter *= uNoiseStrength / uResolution;
    uv += jitter * inside;


    vec4 blurred = vec4(
        texture(VerticalBlurRT, uv + totalOffset).r,
        texture(VerticalBlurRT, uv + totalOffset * uChromaticGreen).g,
        texture(VerticalBlurRT, uv + totalOffset * uChromaticBlue).b,
        1.0
    );

    float fresnelVal = fresnelSchlick(sdfN * borderBlend, uFresnelPower);

    vec4 original = texture(Background, uv);

    vec3 glassColor = blurred.rgb;
    glassColor += fresnelVal * uFresnelStrength;
    glassColor  = mix(glassColor, glassColor * uTint, inside * uTintStrength);

    outColor = mix(original, vec4(glassColor, 1.0), inside);
}
