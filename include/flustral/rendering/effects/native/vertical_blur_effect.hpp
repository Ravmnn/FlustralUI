#pragma once

#include <flustral/rendering/effects/native/native_shaders.hpp>
#include <flustral/rendering/effects/native/blur_effect.hpp>




class VerticalBlurEffect : public BlurEffect
{
public:
    VerticalBlurEffect()
        : BlurEffect(std::make_unique<Shader>(LoadShaderFromMemory(nullptr, NativeShaders::VerticalBlurShader)),
            Vector2{ (float)GetScreenWidth(), (float)GetScreenHeight() },
            8,
            4
        )
    {}
};