#pragma once

#include <raylib.h>

#include <flustral/rendering/renderer.hpp>




class TextureRenderer : public Renderer
{
private:
    RenderTexture2D _texture;


public:
    TextureRenderer() noexcept
        : TextureRenderer(GetScreenWidth(), GetScreenHeight()) {}

    explicit TextureRenderer(const unsigned int width, const unsigned int height) noexcept
        : _texture(LoadRenderTexture(width, height)) {}


    ~TextureRenderer() { UnloadRenderTexture(_texture); }


    void begin_render() noexcept override { BeginTextureMode(_texture); ClearBackground(clear_color); }
    void end_render() noexcept override { EndTextureMode(); }


    Texture contents() const noexcept override { return _texture.texture; }
};