#include <flustral/scene.hpp>

#include <flustral/drawable.hpp>
#include <flustral/rendering/effects/native/horizontal_blur_effect.hpp>
#include <flustral/rendering/effects/native/vertical_blur_effect.hpp>
#include <flustral/texture_sample.hpp>




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
        constexpr float DownSamplingFactor = 2.0f;

        const RenderTexture down_sampled = TextureSample::down_sample(layer->draw_and_get(), DownSamplingFactor);
        const Vector2 resolution = { (float)down_sampled.texture.width, (float)down_sampled.texture.height };

        _horizontal_blur->resolution.value = resolution;
        _vertical_blur->resolution.value = resolution;

        const RenderTexture horizontal_blurred = _horizontal_blur_pass.apply(down_sampled.texture);
        const RenderTexture vertical_blurred = _vertical_blur_pass.apply(horizontal_blurred.texture);
        const RenderTexture up_sampled = TextureSample::up_sample(vertical_blurred.texture, DownSamplingFactor);

        _window_renderer.begin_render();
        DrawTextureRec(up_sampled.texture, { 0, 0, (float)up_sampled.texture.width, (float)-up_sampled.texture.height }, {}, WHITE);
        _window_renderer.end_render();

        UnloadRenderTexture(horizontal_blurred);
        UnloadRenderTexture(vertical_blurred);
        UnloadRenderTexture(down_sampled);
        UnloadRenderTexture(up_sampled);

        break;
    }
}