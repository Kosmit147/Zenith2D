#include "Player.hpp"

Player::Player(const zth::Texture& texture) : Sprite(texture) {}

void Player::on_update()
{
    const auto delta_time = static_cast<float>(zth::engine->delta_time());
    auto& input = zth::engine->input;

    auto position = get_position();

    float new_x = position.x;
    float new_y = position.y;

    if (input.is_key_pressed(zth::Key::A))
        new_x -= _movement_speed * delta_time;

    if (input.is_key_pressed(zth::Key::D))
        new_x += _movement_speed * delta_time;

    if (input.is_key_pressed(zth::Key::W))
        new_y -= _movement_speed * delta_time;

    if (input.is_key_pressed(zth::Key::S))
        new_y += _movement_speed * delta_time;

    set_position({ new_x, new_y });
}
