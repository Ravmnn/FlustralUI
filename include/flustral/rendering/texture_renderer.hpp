#pragma once

#include <raylib.h>

#include <flustral/rendering/renderer.hpp>




class TextureRenderer : public Renderer
{
private:
    RenderTexture _texture;


public:
    TextureRenderer() noexcept
        : TextureRenderer(GetScreenWidth(), GetScreenHeight()) {}

    explicit TextureRenderer(const unsigned int width, const unsigned int height) noexcept;
    virtual ~TextureRenderer() { UnloadRenderTexture(_texture); }


    void begin_render() noexcept override;
    void end_render() noexcept override;


    Texture contents() const noexcept override { return _texture.texture; }


    static void draw_y_inverted_texture(const Texture& texture, const Vector2& position = {}) noexcept;
};