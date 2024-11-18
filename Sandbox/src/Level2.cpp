#include "Level2.hpp"

#include <battery/embed.hpp>

const static auto you_won_texture = b::embed<"assets/you_won.png">();

Level2::Level2()
    : _you_won_texture(
        zth::Texture::from_memory(reinterpret_cast<const zth::u8*>(you_won_texture.data()), you_won_texture.size())
            .value_or(zth::Texture{})),
      _you_won(_you_won_texture)
{
    _you_won.set_position({ 450.0f, 100.0f });
    _you_won.scale(2.0f);
    register_drawable(_you_won);
}
