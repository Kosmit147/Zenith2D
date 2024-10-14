#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <functional>
#include <string_view>

#include "Color.h"
#include "Event.h"

struct Resolution
{
	uint32_t width;
	uint32_t height;

	explicit inline operator sf::VideoMode() const { return sf::VideoMode { width, height }; }
};

struct WindowParams
{
	std::string_view title;
	Resolution resolution;
	bool fullscreen = false;
	uint32_t framerate_limit = 60;
};

using OnInitFunc = std::function<void()>;
using OnUpdateFunc = std::function<void(uint64_t)>;
using OnEventFunc = std::function<void(const Event&)>;

class Engine
{
public:
	Color clear_color = Color::Black;

public:
    Engine(const WindowParams& window_params, const OnInitFunc& init_func, const OnUpdateFunc& update_func, const OnEventFunc& event_func);
    Engine(const WindowParams& window_params, OnInitFunc&& init_func, OnUpdateFunc&& update_func, OnEventFunc&& event_func);

	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;

	void run();

private:
	sf::RenderWindow _window;
	OnInitFunc _init_func;
	OnUpdateFunc _update_func;
	OnEventFunc _event_func;
};