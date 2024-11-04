#pragma once

#include <Zenith/Core/Core.hpp>
#include <Zenith/Graphics/Shapes/Shapes.hpp>

class Player : public zth::Updatable, public zth::EventListener
{
public:
    float movement_speed = 100.0f;

public:
    void update(double delta_time) override;
    void on_event(const zth::Event& event, double delta_time) override;
    void on_key_pressed(const zth::KeyEvent& event, double delta_time);

    void set_position(const zth::Vec2f& new_pos);

    auto& get_shape() const { return _rect_shape; }

private:
    zth::Vec2f _position = { 0.0f, 0.0f };
    zth::RectangleShape _rect_shape{ { { 0.0f, 0.0f }, { 100.0f, 100.0f } }, zth::Color::red };
};
