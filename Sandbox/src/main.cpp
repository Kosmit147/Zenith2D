#include "Engine/Engine.h"

static void on_init()
{
    std::println("On Init");
}

static void on_update(PrimitiveRenderer& renderer, [[maybe_unused]] Logger& logger, uint64_t delta_time)
{
    std::println("On Update with delta time: {} ms.", delta_time);

    Line lines[] = {
        Line{ { 2.0f, 2.0f }, { 2.0f, 1000.0f } },
        Line{ { 2.0f, 1000.0f }, { 150.0f, 600.0f } },
        Line{ { 150.0f, 600.0f }, { 1000.0f, 27.0f } },
    };

    renderer.draw(Point2D{ 300.0f, 300.0f }, Color::Magenta);
    renderer.draw(lines, Color::Green, LineRenderingAlgorithm::Incremental);
}

static void on_event(const Event& e)
{
    switch (e.type())
    {
    case EventType::KeyPressed:
    {
        auto& key_event = e.key_event();
        std::println("{} key pressed.", to_string(key_event.key));
    }
    break;
    case EventType::KeyReleased:
    {
        auto& key_event = e.key_event();
        std::println("{} key released.", to_string(key_event.key));
    }
    break;
    default:
        break;
    }
}

int main()
{
    static constexpr WindowParams window_params = {
        .title = "Sandbox",
        .resolution = { 1920, 1080 },
        .fullscreen = false,
        .framerate_limit = 60,
    };

    Engine e{ window_params, on_init, on_update, on_event };

    e.logger().log_target = LogTarget::ConsoleAndFile;
    e.logger().log_file_path = "../log.txt";
    e.logger().log("Logger Test", LogSeverity::Error);

    e.window().clear_color = Color::Black;
    e.run();
}
