//
// Created by lolpie on 10/20/22.
//
#pragma once
#include "SFML/Main.hpp"
#include "../../helping/structs.h"
#include "../../helping/perfect_collision.h"
#include "../../settings/constants_and_defines.h"
#include "../../event/observer_object.h"
#include "../parent/includes.h"
#include "hoverable.h"
#include <SFML/Window/Event.hpp>

namespace objects{ namespace mixins
{
    using events::observer_list;


    class Clickable: public Hoverable
    {
    protected:
        event_function_type press_function;
        event_function_type release_function;
        virtual bool press(sf::Event sfml_event)
        {
            if(!is_mouse_in({sfml_event.mouseButton.x, sfml_event.mouseButton.y}))
            {
                is_pressed = false;
                return false;
            }
            is_pressed = true;
            return press_function(sfml_event);

        }
        virtual bool release(sf::Event sfml_event)
        {
            auto old_is_pressed = is_pressed;
            is_pressed = false;
            if(!old_is_pressed || !is_mouse_in({sfml_event.mouseButton.x, sfml_event.mouseButton.y}))
                return false;
            return release_function(sfml_event);

        }
        bool is_pressed = false;
    public:
		bool with_check_transparency = true;
		bool get_is_pressed()
		{
			return is_pressed;
		}
        virtual int bind_press(event_function_type function, observer_list& observer)
        {
            press_function = function;
            return observer.bind(sf::Event::MouseButtonPressed, [this](sf::Event event) {
                return this->press(event);
            }, this);
        }
        virtual int bind_release(event_function_type function, observer_list& observer)
        {
            release_function = function;
			if(!press_function)
				bind_press([](sf::Event event){ return true; }, observer);
            return observer.bind(sf::Event::MouseButtonReleased, [this](sf::Event event) {
                return this->release(event);
            }, this);
        }

    };
}}
