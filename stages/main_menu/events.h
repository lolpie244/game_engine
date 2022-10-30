//
// Created by lolpie on 11/25/21.
//

#pragma once
#include "../../helping/includes.h"
#include "main_menu.h"
#include "../../settings/constants_and_defines.h"
#include "../../objects/includes.h"
#include <iostream>

namespace main_menu_np
{
    using namespace std;
    using namespace sf;
    using structs::Point, helping_function::get_scaled_mouse_position, helping_function::get_mouse_position,
            helping_function::get_min_scaled_mouse_position;

    bool construct_convex_press(sf::Event event, main_menu* screen_stage)
    {
        Point mouse = get_min_scaled_mouse_position(*screen_stage->window);
        sh_p<objects::figures::figure_object> point(
                new objects::figures::figure_object({mouse.x, mouse.y, 1.1}, {100, 100}, textures::dot));

        screen_stage->points.push_back(point);
		screen_stage->bezier.add_point({mouse.x, mouse.y});

        point->set_scale<objects::mixins::relative_position_scale>();

        screen_stage->elements.push_back(point.get());
        if(screen_stage->points.size() >= 5)
        {
            screen_stage->elements.remove_object(screen_stage->points[screen_stage->points.size() - 5].get());
            screen_stage->points.erase(screen_stage->points.begin());
        }
        return true;
    }

    void main_menu::init_event_objects()
    {
        start_button.bind_scale<objects::mixins::relative_position_scale>(window, elements.event_manager);
        slider.bind_scale<objects::mixins::relative_position_scale, objects::mixins::composite_relative_scale>(window, elements.event_manager);
		// bezier.set_draw<objects::mixins::ObjectCommonDraw, typename objects::figures::BezierDraw>();

        start_button.bind_press([](sf::Event event){return true;}, elements.event_manager);
        background.bind_press([this](sf::Event event) { return construct_convex_press(event, this); },
                              elements.event_manager);
        slider.bind_slider([this](sf::Event event) {
            std::cout << this->slider.get_value() << '\n';
            return true;
        }, elements.event_manager);

        drag_test.bind_drag([this](sf::Event event){
            this->drag_test.set_position(this->drag_test.get_position() + this->drag_test.get_moved_to());
            return true;
            }, elements.event_manager);
    }

}
