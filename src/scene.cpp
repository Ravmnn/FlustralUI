#include <flustral/scene.hpp>

#include <flustral/drawable.hpp>
#include <flustral/rendering/effects/native/horizontal_blur_effect.hpp>
#include <flustral/rendering/effects/native/vertical_blur_effect.hpp>




Scene::Scene() noexcept
    : _horizontal_blur_pass(EffectPass(std::make_unique<HorizontalBlurEffect>())),
        _vertical_blur_pass(EffectPass(std::make_unique<VerticalBlurEffect>())),
        _window_renderer()
{
    _window_renderer.use_buffer_texture = false;

    _horizontal_blur = dynamic_cast<HorizontalBlurEffect*>(_horizontal_blur_pass.effect());
    _vertical_blur = dynamic_cast<VerticalBlurEffect*>(_vertical_blur_pass.effect());
}




void Scene::update() noexcept
{
    for (auto& layer : layers)
        layer->update();
}




void Scene::draw() noexcept
{
    for (auto& layer : layers)
    {
        Texture texture = layer->draw_and_get();

        _horizontal_blur->texture.value = texture;
        _vertical_blur->texture.value = texture;

        texture = _horizontal_blur_pass.apply(texture);
        texture = _vertical_blur_pass.apply(texture);

        _window_renderer.begin_render();
        const Rectangle source = Rectangle{ 0, 0, texture.width, -texture.height };
        DrawTextureRec(texture, source, { 0, 0 }, WHITE);
        _window_renderer.end_render();

        break;
    }
}