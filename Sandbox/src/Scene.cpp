#include "Scene.hpp"

#include <battery/embed.hpp>

const static auto emoji = b::embed<"assets/emoji.png">();

Scene::Scene()
    : _player_texture(zth::Texture::from_memory(reinterpret_cast<const zth::u8*>(emoji.data()), emoji.size())
                          .value_or(zth::Texture{})),
      _player(_player_texture)
{
    register_updatable(_player);
}

Scene::~Scene()
{
    deregister_updatable(_player);
}

void Scene::on_update()
{
    zth::engine->window.renderer.draw(_player);
}
