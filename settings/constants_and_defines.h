//
// Created by lolpie on 26.06.22.
//
#pragma once
#include <SFML/Window/Window.hpp>
#include <functional>
#include <SFML/Graphics.hpp>
#include <limits>
#include <memory>

#define sh_p std::shared_ptr

using event_function_type = std::function<bool(sf::Event)>;
namespace constants
{
	std::shared_ptr<sf::RenderWindow> current_window;
    double inf = std::numeric_limits<double>::infinity();
    double min_d = std::numeric_limits<double>::min();
    double max_d = std::numeric_limits<double>::max();
}
