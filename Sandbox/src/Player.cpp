#include "Player.hpp"

Player::Player(const zth::Texture& texture) : Sprite(texture) {}

void Player::on_update([[maybe_unused]] const double delta_time)
{
    // zth::Logger::print_notification("Player Update");

    // const auto dt = static_cast<float>(delta_time);

    // auto position = get_position();

    // float new_x = position.x;
    // float new_y = position.y;

    // if (is_key_pressed(zth::Key::A))
    //     new_x -= movement_speed * dt;

    // if (is_key_pressed(zth::Key::D))
    //     new_x += movement_speed * dt;

    // if (is_key_pressed(zth::Key::W))
    //     new_y -= movement_speed * dt;

    // if (is_key_pressed(zth::Key::S))
    //     new_y += movement_speed * dt;

    // set_position({ new_x, new_y });
}

void Player::on_event(const zth::Event& event, const double delta_time)
{
    switch (event.type())
    {
    case zth::EventType::KeyPressed:
    {
        auto& key_event = event.key_event();
        on_key_pressed(key_event, delta_time);
    }
    break;
    default:
        break;
    }
}

void Player::on_key_pressed(const zth::KeyEvent& event, const double delta_time)
{
    (void)event;
    (void)delta_time;
}

// void Player::on_update([[maybe_unused]] const double delta_time)
// {
//     zth::Logger::print_notification("Player Update");
// }
//
// void Player::on_event(const zth::Event& event, const double delta_time)
// {
//     switch (event.type())
//     {
//     case zth::EventType::KeyPressed:
//     {
//         auto& key_event = event.key_event();
//         on_key_pressed(key_event, delta_time);
//     }
//     break;
//     default:
//         break;
//     }
// }
//
// void Player::on_key_pressed(const zth::KeyEvent& event, const double delta_time)
// {
//     const auto dt = static_cast<float>(delta_time);
//
//     float new_x = _position.x;
//     float new_y = _position.y;
//
//     switch (event.key)
//     {
//     case zth::Key::A:
//         new_x -= movement_speed * dt;
//         break;
//     case zth::Key::D:
//         new_x += movement_speed * dt;
//         break;
//     case zth::Key::W:
//         new_y -= movement_speed * dt;
//         break;
//     case zth::Key::S:
//         new_y += movement_speed * dt;
//         break;
//     default:
//         break;
//     }
//
//     set_position({ new_x, new_y });
// }
//
// void Player::set_position(const zth::Vec2f& new_pos)
// {
//     _position = new_pos;
//     _rect_shape.rect.position = _position;
// }
