#include <flustral/components/texture.hpp>




TextureComponent::TextureComponent(const Vector2& position, const Vector2& size, const Texture& texture) noexcept
    : Component(position), size(size), _texture(texture)
{}




void TextureComponent::draw() noexcept
{
    DrawTexturePro(_texture, { 0, 0, (float)_texture.width, (float)_texture.height }, { position.x, position.y, size.x, size.y }, {}, 0, tint);
}