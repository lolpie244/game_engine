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
#include "../draw_bezier/stage.h"

namespace detail_bezier_np
{
    using namespace std;
    using namespace sf;
	using namespace objects;
    using structs::Point, helping_function::get_mouse_position, helping_function::round;

	bool detail_bezier_press(sf::Event event, detail_bezier* screen_stage)
    {
		Point mouse = get_mouse_position(*screen_stage->window);
		screen_stage->bezier->push_back(mouse, screen_stage->elements.event_manager);
		return true;
    }
	void update_bezier(detail_bezier* screen_stage)
	{
		auto display_type = screen_stage->get_current_display_type();
		screen_stage->bezier->set_diaplay_type(display_type);
	}
	bool change_with_helping(sf::Event event, detail_bezier *screen_stage)
	{
		screen_stage->with_points.set_value(false);
		update_bezier(screen_stage);
		return true;
	}

	bool change_with_points(sf::Event event, detail_bezier *screen_stage)
	{
		screen_stage->with_helping.set_value(false);
		update_bezier(screen_stage);
		return true;
	}

	bool clear_beziers(sf::Event event, detail_bezier* screen_stage)
	{
		screen_stage->bezier->clear();
		return true;
	}
	bool to_draw_press(sf::Event event, detail_bezier* screen_stage)
	{
		(new draw_bezier_np::draw_bezier(*screen_stage->main_info))->main();
		return true;
	}
	void detail_bezier::init_event_objects()
    {

		with_points.set_scale<mixins::attach_position_scale>();
		with_helping.set_scale<mixins::attach_position_scale>();
		to_draw.set_scale<mixins::attach_position_scale>();
		clear_button.set_scale<mixins::attach_position_scale>();

		clear_button.bind_release([this](sf::Event event) { return clear_beziers(event, this); }, elements.event_manager);
		to_draw.bind_release([this](sf::Event event) { return to_draw_press(event, this); }, elements.event_manager);

        slider.bind_scale<mixins::attach_position_scale, mixins::composite_attach_scale>(window, elements.event_manager);
		bezier->set_draw<mixins::ObjectCommonDraw, objects::figures::BezierDraw>();
        background.bind_press([this](sf::Event event) { return detail_bezier_press(event, this); }, elements.event_manager);
		slider.bind_slider([this](sf::Event event) {
				this->bezier->set_max_t(round(this->slider.get_value(), 2));
				return true;
			},
			this->elements.event_manager);

		with_points.bind_press([this](sf::Event event) {return change_with_points(event, this); }, elements.event_manager);
		with_helping.bind_press([this](sf::Event event) {return change_with_helping(event, this); }, elements.event_manager);
    }

}
