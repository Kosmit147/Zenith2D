#include "Dragon.hpp"

#include "Level2.hpp"

static constexpr zth::SpriteSize dragon_sprite_size = {
    .width = 192,
    .height = 192,
};

Dragon::Dragon(const zth::Texture& texture, const zth::Sprite& gold_bar)
    : AnimatedSprite(texture, dragon_sprite_size, 3 * 4, 0.1f), _gold_bar(gold_bar)
{}

void Dragon::on_update()
{
    const auto delta_time = static_cast<float>(zth::engine->delta_time());
    auto& input = zth::engine->input;

    auto position = get_position();

    float new_x = position.x;
    float new_y = position.y;

    _walking = false;

    if (input.is_key_pressed(zth::Key::A))
    {
        new_x -= _movement_speed * delta_time;
        _direction = Direction::Left;
        _walking = true;
    }

    if (input.is_key_pressed(zth::Key::D))
    {
        new_x += _movement_speed * delta_time;
        _direction = Direction::Right;
        _walking = true;
    }

    if (input.is_key_pressed(zth::Key::W))
    {
        new_y -= _movement_speed * delta_time;
        _direction = Direction::Up;
        _walking = true;
    }

    if (input.is_key_pressed(zth::Key::S))
    {
        new_y += _movement_speed * delta_time;
        _direction = Direction::Down;
        _walking = true;
    }

    auto center = bounds().center();

    if (_gold_bar.bounds().contains(center))
        zth::engine->change_scene(std::make_unique<Level2>());

    set_position({ new_x, new_y });
}

zth::u32 Dragon::next_frame()
{
    static zth::Timer timer;
    static zth::u32 remainder = 0;

    if (!_walking)
        timer.reset();

    if (timer.elapsed_s() > _walking_animation_length)
    {
        timer.reset();
        remainder = (remainder + 1) % 3;
    }

    switch (_direction)
    {
        using enum Direction;
    case Up:
        return 9 + remainder;
    case Right:
        return 6 + remainder;
    case Down:
        return 0 + remainder;
    case Left:
        return 3 + remainder;
    }

    return 0;
}
