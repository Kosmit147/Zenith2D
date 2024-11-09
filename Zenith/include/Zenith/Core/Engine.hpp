#pragma once

#include "Zenith/Core/EventDispatcher.hpp"
#include "Zenith/Core/FrameCounter.hpp"
#include "Zenith/Core/Updater.hpp"
#include "Zenith/Platform/Input/Input.hpp"
#include "Zenith/Platform/Window.hpp"
#include "Zenith/Utility/GlobalAccessPtr.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Engine
{
public:
    Window window;
    Input input;

public:
    ZTH_NO_COPY_NO_MOVE(Engine)
    ~Engine();

    auto delta_time() const { return _delta_time; }
    auto fps() const { return _frame_counter.get_fps(); }

    void register_updatable(Updatable& updatable);
    void deregister_updatable(const Updatable& updatable);

    void register_listener(EventListener& listener);
    void register_listener(EventType event_type, EventListener& listener);
    void deregister_listener(EventType event_type, const EventListener& listener);
    void deregister_listener(const EventListener& listener);

    friend class GlobalAccessPtr<Engine>;
    friend class Application;

private:
    double _delta_time = 0.0;
    FrameCounter _frame_counter;
    EventDispatcher _event_dispatcher;
    Updater _updater;

private:
    explicit Engine(const WindowSpec& window_spec);
};

inline GlobalAccessPtr<Engine> engine;

} // namespace zth
