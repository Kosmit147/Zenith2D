#include "Engine/Engine.h"
#include "Engine/Event.h"

#include <print>

static void on_init()
{
    std::println("On Init");
}

static void on_update(uint64_t delta_time)
{
    // std::println("On Update with delta time: {}", delta_time);
}

static void on_event(const Event& e)
{
	switch (e.type())
	{
	case EventType::KeyPressed:
		{
			auto& key_event = e.key_event();
			std::println("{} key pressed.", key_to_string(key_event.key));
		}
		break;
	case EventType::KeyReleased:
		{
			auto& key_event = e.key_event();
			std::println("{} key released.", key_to_string(key_event.key));
		}
		break;
	}
}

int main()
{
	static constexpr WindowParams window_params = {
		.title = "Sandbox",
		.resolution = { 1920, 1080 },
		.fullscreen = false,
		.framerate_limit = 10,
	};

	Engine e{ window_params, on_init, on_update, on_event };
	e.run();
}
