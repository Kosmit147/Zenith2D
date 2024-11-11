#include "Scene.hpp"

Scene::Scene()
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
