#pragma once

#include <Zenith/Core/Scene.hpp>
#include <Zenith/Graphics/Renderer.hpp>

class PrimitiveRendererTest : public zth::Scene
{
public:
    explicit PrimitiveRendererTest(zth::Renderer& renderer) : _renderer(renderer) {}

private:
    zth::Renderer& _renderer;

private:
    void on_update() override;

    void sfml_primitive_renderer_test() const;
    void custom_primitive_renderer_test() const;
    void draw_primitives() const;
};
