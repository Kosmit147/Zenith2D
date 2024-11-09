#include "Player.hpp"

Player::Player(const zth::Texture& texture) : Sprite(texture) {}

void Player::on_update()
{
    const auto delta_time = static_cast<float>(zth::engine->delta_time());
    auto& input = zth::engine->input;

    zth::Logger::print_notification("Player Update");

    auto position = get_position();

    float new_x = position.x;
    float new_y = position.y;

    if (input.is_key_pressed(zth::Key::A))
        new_x -= movement_speed * delta_time;

    if (input.is_key_pressed(zth::Key::D))
        new_x += movement_speed * delta_time;

    if (input.is_key_pressed(zth::Key::W))
        new_y -= movement_speed * delta_time;

    if (input.is_key_pressed(zth::Key::S))
        new_y += movement_speed * delta_time;

    set_position({ new_x, new_y });
}

void Player::on_event(const zth::Event& event)
{
    switch (event.type())
    {
    case zth::EventType::KeyPressed:
    {
        auto& key_event = event.key_event();
        on_key_pressed(key_event);
    }
    break;
    default:
        break;
    }
}

void Player::on_key_pressed(const zth::KeyEvent& event)
{
    zth::logger->log_notification("{} key pressed.", to_string(event.key));
}
