//
// Created by lolpie on 10/22/22.
//
#pragma once
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include "../parent/includes.h"
#include "../../helping/structs.h"
#include "../../event/observer_object.h"
#include "clickable.h"
#include <iostream>
#include <chrono>

namespace objects{ namespace mixins
{
	using namespace std::chrono;
    using parent::object, structs::Point, events::observer_list;

    class Draggable: public Clickable
    {
    private:
        Point last_mouse_position;
    protected:
        event_function_type on_drag;
        Point moved_to;
    public:
        Point get_moved_to()
        {
            return moved_to;
        }
        int bind_press(event_function_type function, observer_list& observer) override
        {
            Clickable::bind_press([this, function](sf::Event event){
                this->last_mouse_position = {event.mouseButton.x, event.mouseButton.y};
                return function(event);
            }, observer);
        }
        int bind_drag(event_function_type function, observer_list& observer)
        {
            if(!press_function)
                bind_press([this](sf::Event event){ return true; }, observer);

            if(!release_function)
                bind_release([this](sf::Event event){ return false; }, observer);

            return observer.bind(sf::Event::MouseMoved, [this, function](sf::Event event)
            {
                Point mouse_position = {event.mouseMove.x, event.mouseMove.y};
                this->moved_to = mouse_position - last_mouse_position;
                last_mouse_position = mouse_position;
                if(!this->is_pressed)
                    return false;
                return function(event);
            }, this);
        }
    };
	class DraggableMove: public Draggable
	{
	public:
		int bind_drag(event_function_type function, observer_list& observer)
		{
			return Draggable::bind_drag([this, function](sf::Event event){ this->set_position(this->position + this->moved_to); function(event); return true; }, observer);
		}
	};
}}
