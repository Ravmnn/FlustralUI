#pragma once

#include <flustral/components/component.hpp>




class TextureComponent : public Component
{
private:
    Texture _texture;


public:
    Color tint = WHITE;
    Vector2 size;


    TextureComponent(const Vector2& position, const Vector2& size, const Texture& texture) noexcept;
    virtual ~TextureComponent() { UnloadTexture(_texture); }


    void draw() noexcept override;


    const Texture& texture() const noexcept { return _texture; }
};