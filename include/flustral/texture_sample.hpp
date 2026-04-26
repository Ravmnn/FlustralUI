#pragma once

#include <raylib.h>




class TextureSample
{
public:
    static RenderTexture down_sample(const Texture& source, const float factor) noexcept;
    static RenderTexture up_sample(const Texture& source, const float factor) noexcept;
};