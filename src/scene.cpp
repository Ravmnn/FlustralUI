#include <flustral/scene.hpp>

#include <optional>

#include <flustral/drawable.hpp>
#include <flustral/components/surface.hpp>
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
    // TODO: surfaces cannot exist on the background layer
    // TODO: create LocalRenderTexture that unloads itself when destructed

    std::optional<RenderTexture> background_texture;

    for (auto& layer : layers)
    {
        if (!background_texture)
        {
            background_texture = layer->draw_and_get();
            continue;
        }

        RenderTexture blurred_background_texture = _blur_pass.apply(background_texture.value().texture);

        for (auto& component : layer->components)
        {
            SurfaceComponent* surface = dynamic_cast<SurfaceComponent*>(component.get());
            SurfaceEffect* effect = dynamic_cast<SurfaceEffect*>(&surface->effect());
            effect->background.value = background_texture.value().texture;
            effect->blurred_background.value = blurred_background_texture.texture;

            background_texture = EffectPass(*effect).apply(background_texture.value().texture);
        }

        UnloadRenderTexture(blurred_background_texture);
    }


    _window_renderer.begin_render();
    TextureRenderer::draw_y_inverted_texture(background_texture.value().texture);
    _window_renderer.end_render();
}