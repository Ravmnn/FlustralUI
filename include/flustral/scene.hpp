#pragma once

#include <raylib.h>

#include <flustral/rendering/effects/effect_pass.hpp>
#include <flustral/rendering/window_renderer.hpp>
#include <flustral/scene_layer.hpp>




class HorizontalBlurEffect;
class VerticalBlurEffect;


class Scene : Updateable, Drawable
{
private:
    HorizontalBlurEffect* _horizontal_blur;
    VerticalBlurEffect* _vertical_blur;

    EffectPass _horizontal_blur_pass;
    EffectPass _vertical_blur_pass;

    WindowRenderer _window_renderer;


public:
    std::vector<std::unique_ptr<SceneLayer>> layers;


    Scene() noexcept;


    void update() noexcept override;
    void draw() noexcept override;
};