#include "Scene.hpp"

#include <battery/embed.hpp>

const static auto emoji = b::embed<"assets/emoji.png">();
const static auto dragon_sprite_sheet = b::embed<"assets/dragon.png">();

Scene::Scene()
    : _dragon_texture(zth::Texture::from_memory(reinterpret_cast<const zth::u8*>(dragon_sprite_sheet.data()),
                                                dragon_sprite_sheet.size())
                          .value_or(zth::Texture{})),
      _dragon(_dragon_texture),
      _player_texture(zth::Texture::from_memory(reinterpret_cast<const zth::u8*>(emoji.data()), emoji.size())
                          .value_or(zth::Texture{})),
      _player(_player_texture)
{
    // register_updatable(_player);
    register_updatable(_dragon);
    _dragon.scale({ 3.0f, 3.0f });
}

Scene::~Scene()
{
    // deregister_updatable(_player);
    deregister_updatable(_dragon);
}

void Scene::on_update()
{
    _dragon.animate();
    zth::engine->window.renderer.draw(_player);
    zth::engine->window.renderer.draw(_dragon);
}
