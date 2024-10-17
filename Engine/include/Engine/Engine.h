#pragma once

#include <cstdint>
#include <functional>
#include <string_view>

#include "Color.h"
#include "Event.h"
#include "Logger.h"
#include "PrimitiveRenderer.h"
#include "Window.h"

using OnInitFunc = std::function<void()>;
using OnUpdateFunc = std::function<void(uint64_t)>;
using OnEventFunc = std::function<void(const Event&)>;

class Engine
{
public:
    Engine(const WindowParams& window_params, const OnInitFunc& init_func, const OnUpdateFunc& update_func,
           const OnEventFunc& event_func);
    Engine(const WindowParams& window_params, OnInitFunc&& init_func, OnUpdateFunc&& update_func,
           OnEventFunc&& event_func);

    void run();

    inline Logger& logger() { return _logger; }
    inline const Logger& logger() const { return _logger; }

    inline Window& window() { return _window; }
    inline const Window& window() const { return _window; }

    inline PrimitiveRenderer& renderer() { return _renderer; }
    inline const PrimitiveRenderer& renderer() const { return _renderer; }

private:
    OnInitFunc _init_func;
    OnUpdateFunc _update_func;
    OnEventFunc _event_func;

    Window _window;
    Logger _logger;
    PrimitiveRenderer _renderer;
};
