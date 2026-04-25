#pragma once

#include <flustral/rendering/effects/native/native_shaders.hpp>
#include <flustral/rendering/effects/native/blur_effect.hpp>




class HorizontalBlurEffect : public BlurEffect
{
public:
    HorizontalBlurEffect()
        : BlurEffect(std::make_unique<Shader>(LoadShaderFromMemory(nullptr, NativeShaders::HorizontalBlurShader)),
            Vector2{ (float)GetScreenWidth(), (float)GetScreenHeight() },
            8,
            4
        )
    {}
};