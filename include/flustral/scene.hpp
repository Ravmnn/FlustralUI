#pragma once

#include <raylib.h>

#include <flustral/rendering/effects/native/gaussian_blur_effect_pass.hpp>
#include <flustral/rendering/window_renderer.hpp>
#include <flustral/scene_layer.hpp>




class HorizontalBlurEffect;
class VerticalBlurEffect;


class Scene : Updateable, Drawable
{
private:
    GaussianBlurEffectPass _blur_pass;

    WindowRenderer _window_renderer;


public:
    std::vector<std::unique_ptr<SceneLayer>> layers;


    Scene() noexcept;


    void update() noexcept override;
    void draw() noexcept override;
};