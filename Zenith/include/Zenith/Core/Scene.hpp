#pragma once

#include "Zenith/Core/EventDispatcher.hpp"
#include "Zenith/Core/Updater.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Drawable;
class Animatable;

class Scene
{
public:
    virtual ~Scene() = default;
    ZTH_NO_COPY_NO_MOVE(Scene)

    friend class Engine;

protected:
    explicit Scene() = default;

    void register_updatable(Updatable& updatable);
    void deregister_updatable(const Updatable& updatable);
    
    void register_event_listener(EventListener& listener);
    void register_event_listener(EventType event_type, EventListener& listener);
    void deregister_event_listener(EventType event_type, const EventListener& listener);
    void deregister_event_listener(const EventListener& listener);

    void register_drawable(Drawable& drawable);
    void deregister_drawable(Drawable& drawable);

    void register_animatable(Animatable& animatable);
    void deregister_animatable(Animatable& animatable);

private:
    Updater _updater;
    EventDispatcher _event_dispatcher;
    std::vector<Drawable*> _drawables;
    std::vector<Animatable*> _animatables;

private:
    void update();
    void dispatch_event(const Event& event);

    virtual void on_load() {}
    virtual void on_update() {}
    virtual void on_event([[maybe_unused]] const Event& event) {}
};

} // namespace zth
