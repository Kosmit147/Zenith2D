#pragma once

#include <memory>

#include "Zenith/Core/FrameCounter.hpp"
#include "Zenith/Core/Scene.hpp"
#include "Zenith/Platform/Event.hpp"
#include "Zenith/Platform/Input/Input.hpp"
#include "Zenith/Platform/Window.hpp"
#include "Zenith/Utility/GlobalAccessPtr.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Updatable;
class EventListener;

class Engine
{
public:
    Window window;
    Input input;
    std::unique_ptr<Scene> scene;

public:
    ~Engine();
    ZTH_NO_COPY_NO_MOVE(Engine)

    auto delta_time() const { return _delta_time; }
    auto fps() const { return _frame_counter.get_fps(); }

    // changes the scene in the next frame
    void change_scene(std::unique_ptr<Scene> new_scene);

    friend class GlobalAccessPtr<Engine>;
    friend class Application;

private:
    double _delta_time = 0.0;
    FrameCounter _frame_counter;
    std::unique_ptr<Scene> _queued_scene;

private:
    explicit Engine(const WindowSpec& window_spec);

    void on_update();
    void on_event(const Event& event);
    void on_input_event(const Event& event);
};

inline GlobalAccessPtr<Engine> engine;

} // namespace zth
