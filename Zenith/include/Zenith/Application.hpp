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
    inline Application(const ApplicationSpec& spec = {}) : _window(spec.window_spec), _logger(spec.logger_spec) {}

    Application(const Application& other) = delete;

    virtual inline ~Application(){};

    virtual inline void on_update([[maybe_unused]] u64 delta_time){};
    virtual inline void on_event([[maybe_unused]] const zth::Event& event){};

    void run();

protected:
    // TODO: dont just return the window object
    // create an API for the user
    inline auto& window() { return _window; }
    inline auto& window() const { return _window; }
    // logger is fine for now
    inline auto& logger() { return _logger; }
    inline auto& logger() const { return _logger; }

private:
    // should probably be protected
    Window _window;
    Logger _logger;
};

} // namespace zth
