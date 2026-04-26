#pragma once

#include <flustral/rendering/effects/native/native_shaders.hpp>
#include <flustral/rendering/effects/native/blur_effect.hpp>




class VerticalBlurEffect : public BlurEffect
{
public:
    VerticalBlurEffect(const int samples, const float sigma)
        : BlurEffect(std::make_unique<Shader>(LoadShaderFromMemory(nullptr, NativeShaders::VerticalBlurShader)),
            Vector2{ (float)GetScreenWidth(), (float)GetScreenHeight() },
            samples,
            sigma
        )
    {}
};