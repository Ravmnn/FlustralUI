#include <flustral/scene.hpp>

#include <flustral/drawable.hpp>
#include <flustral/rendering/effects/native/horizontal_blur_effect.hpp>
#include <flustral/rendering/effects/native/vertical_blur_effect.hpp>
#include <flustral/texture_sample.hpp>




Scene::Scene() noexcept
    : _blur_pass(8, 4), _window_renderer()
{
    _blur_pass.down_sample_factor = 2;
    _window_renderer.use_buffer_texture = false;
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
        const RenderTexture blurred = _blur_pass.apply(layer->draw_and_get());

        _window_renderer.begin_render();
        TextureRenderer::draw_y_inverted_texture(blurred.texture);
        _window_renderer.end_render();

        UnloadRenderTexture(blurred);
        break;
    }
}