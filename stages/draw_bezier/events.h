//
// Created by lolpie on 11/25/21.
//

#pragma once
#include "../../helping/includes.h"
#include "stage.h"
#include "../../settings/constants_and_defines.h"
#include "../../objects/includes.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

namespace draw_bezier_np
{
    using namespace std;
    using namespace sf;
	using namespace objects;
    using structs::Point, helping_function::get_scaled_mouse_position, helping_function::get_mouse_position,
            helping_function::get_min_scaled_mouse_position;

	sh_p<objects::figures::Bezier> create_bezier(draw_bezier* screen_stage)
	{
		auto new_bezier = make_shared<objects::figures::Bezier>(Point(0, 0, 3), screen_stage->get_current_display_type());
		new_bezier->set_draw<mixins::ObjectCommonDraw, objects::figures::BezierDraw>();
		screen_stage->elements.push_back(new_bezier.get());
		return new_bezier;
	}
    bool draw_bezier_press(sf::Event event, draw_bezier* screen_stage)
    {
		Point mouse = get_mouse_position(*screen_stage->window);
		if(!screen_stage->beziers.size())
		{
			auto new_bezier = create_bezier(screen_stage);
			screen_stage->beziers.push_back(new_bezier);
		}

		screen_stage->last_bezier()->push_back(mouse, screen_stage->elements.event_manager);
		return true;
    }
	bool draw_bezier_release(sf::Event event, draw_bezier *screen_stage)
	{
		Point mouse = get_mouse_position(*screen_stage->window);
		auto last_point = screen_stage->last_bezier()->last_point();

		if(screen_stage->is_first_point)
		{
			screen_stage->is_first_point = false;
			screen_stage->last_bezier()->push_back(mouse, screen_stage->elements.event_manager);
			screen_stage->next_bezier.points = screen_stage->last_bezier()->points;
			return true;
		}
		screen_stage->last_bezier()->insert((Point)*last_point - (mouse - *last_point), 2, screen_stage->elements.event_manager);

		auto new_bezier = create_bezier(screen_stage);
		screen_stage->beziers.push_back(new_bezier);
		new_bezier->push_back(last_point);
		new_bezier->push_back(mouse, screen_stage->elements.event_manager);

		screen_stage->next_bezier.points = new_bezier->points;

		return true;
	}
	bool change_show_points(sf::Event event, draw_bezier *screen_stage)
	{
		auto display_type = screen_stage->get_current_display_type();
		for(auto bezier: screen_stage->beziers)
			bezier->set_diaplay_type(display_type);
		screen_stage->next_bezier.set_diaplay_type(display_type);
		return true;
	}
	bool clear_beziers(sf::Event event, draw_bezier* screen_stage)
	{
		for(auto obj: screen_stage->beziers)
			screen_stage->elements.remove_object(obj.get());
		screen_stage->beziers.clear();
		screen_stage->is_first_point = true;
		screen_stage->next_bezier.clear();
		return true;
	}
	bool to_detail_press(sf::Event event, draw_bezier* screen_stage)
	{
		screen_stage->exit = true;
		return true;
	}
    void draw_bezier::init_event_objects()
    {
		radio_button.set_scale<mixins::attach_position_scale>();
		to_detail.set_scale<mixins::attach_position_scale>();
		clear_button.set_scale<mixins::attach_position_scale>();

		clear_button.bind_release([this](sf::Event event) { return clear_beziers(event, this); }, elements.event_manager);
		to_detail.bind_release([this](sf::Event event) { return to_detail_press(event, this); }, elements.event_manager);
		radio_button.bind_press([this](sf::Event event) {return change_show_points(event, this); }, elements.event_manager);
        background.bind_press([this](sf::Event event) { return draw_bezier_press(event, this); }, elements.event_manager);
        background.bind_release([this](sf::Event event) { return draw_bezier_release(event, this); }, elements.event_manager);
    }

}
