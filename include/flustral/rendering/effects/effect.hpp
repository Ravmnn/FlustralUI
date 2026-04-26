#pragma once

#include <memory>

#include <raylib.h>

#include <flustral/updateable.hpp>




class Effect : public Updateable
{
private:
    std::unique_ptr<Shader> _shader;


public:
    explicit Effect(std::unique_ptr<Shader> shader) : _shader(std::move(shader)) {}
    virtual ~Effect() { UnloadShader(*_shader); }


    Shader* shader() const noexcept { return _shader.get(); };


    virtual Texture* target_texture() noexcept = 0;
    virtual Vector2* target_texture_resolution() noexcept = 0;
};