//
// Created by lolpie on 11/23/21.
//
#pragma once
#include <SFML/Graphics.hpp>
#include "structs.h"

namespace helping_function
{
    using namespace std;
	using structs::Point;
	int framerate = 60;

    Point get_window_scale(sf::Window &window)
    {
        auto size = window.getSize();
        return {size.x / 1920.0, size.y / 1080.0};
    }
    Point get_mouse_position(sf::Window &window)
    {
        auto local_mouse = sf::Mouse::getPosition(window);
        return {local_mouse.x, local_mouse.y};
    }
    Point get_scaled_mouse_position(sf::Window &window)
    {
        auto local_mouse = sf::Mouse::getPosition(window);
        Point scale = get_window_scale(window);
        return {local_mouse.x / scale.x, local_mouse.y / scale.y};
    }
    Point get_min_scaled_mouse_position(sf::Window &window)
    {
        Point local_mouse = sf::Mouse::getPosition(window);
        Point scale = get_window_scale(window);
        return local_mouse / std::min(scale.x, scale.y);
    }
}
