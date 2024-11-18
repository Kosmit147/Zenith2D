#include "Level1.hpp"

#include <battery/embed.hpp>

const static auto emoji = b::embed<"assets/emoji.png">();
const static auto dragon_sprite_sheet = b::embed<"assets/dragon.png">();
const static auto gold_bars = b::embed<"assets/gold.png">();

Level1::Level1()
    : _dragon_texture(zth::Texture::from_memory(reinterpret_cast<const zth::u8*>(dragon_sprite_sheet.data()),
                                                dragon_sprite_sheet.size())
                          .value_or(zth::Texture{})),
      _dragon(_dragon_texture, _gold_bars),
      _player_texture(zth::Texture::from_memory(reinterpret_cast<const zth::u8*>(emoji.data()), emoji.size())
                          .value_or(zth::Texture{})),
      _player(_player_texture),
      _gold_bars_texture(zth::Texture::from_memory(reinterpret_cast<const zth::u8*>(gold_bars.data()), gold_bars.size())
                             .value_or(zth::Texture{})),
      _gold_bars(_gold_bars_texture)
{
    // register_updatable(_player);
    register_updatable(_dragon);

    register_animatable(_dragon);

    register_drawable(_player);
    register_drawable(_gold_bars);
    register_drawable(_dragon);

    _dragon.scale({ 3.0f, 3.0f });

    _gold_bars.set_position({ 1000.0f, 500.0f });
}

Level1::~Level1()
{
    // deregister_updatable(_player);
    deregister_updatable(_dragon);
}

void Level1::on_update() {}
