#pragma once

#include "Event.hpp"
#include "Logger.hpp"
#include "Typedefs.hpp"
#include "Window.hpp"

namespace zth {

struct ApplicationSpec
{
    WindowSpec window_spec = { .title = "Application", .resolution = { 800, 600 } };
    LoggerSpec logger_spec = { .target = LogTarget::Console };
};

class Application
{
public:
    explicit Application(const ApplicationSpec& spec = {}) : _window(spec.window_spec), _logger(spec.logger_spec) {}

    Application(const Application&) = delete;
    Application(Application&&) = delete;

    virtual ~Application() = default;

    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    void run();

protected:
    Window _window;
    Logger _logger;

private:
    virtual void on_update([[maybe_unused]] u64 delta_time) {}
    virtual void on_event([[maybe_unused]] const Event& event) {}
};

} // namespace zth
