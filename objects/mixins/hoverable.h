#pragma once
#include "SFML/Main.hpp"
#include "../../helping/structs.h"
#include "../../helping/perfect_collision.h"
#include "../../settings/constants_and_defines.h"
#include "../../event/observer_object.h"
#include "../parent/includes.h"
#include <SFML/Window/Event.hpp>

namespace objects{ namespace mixins
{
    using sf::Sprite, structs::Point, events::observer_list, parent::object;


    class Hoverable: virtual public object
    {
		bool is_mouse_in_flag;
    protected:
        event_function_type mouse_in_function;
        event_function_type mouse_out_function;

        virtual bool mouse_in(sf::Event sfml_event)
        {
            if(!is_mouse_in({sfml_event.mouseButton.x, sfml_event.mouseButton.y}))
				if(mouse_out_function)
					return mouse_out(sfml_event);
				else
					return false;
			is_mouse_in_flag = true;
            return mouse_in_function(sfml_event);
        }
		virtual bool mouse_out(sf::Event sfml_event)
		{
			if(!is_mouse_in_flag)
				return false;
			is_mouse_in_flag = false;
			return mouse_out(sfml_event);
		}
    public:
		bool with_check_transparency = true;
        bool is_mouse_in(Point cords)
        {

			Point left_corner = this->get_left_corner();
			Point rigth_corner = this->get_left_corner() + this->size;
			if (!(left_corner.x <= cords.x && left_corner.y <= cords.y &&
				cords.x <= rigth_corner.x && cords.y <= rigth_corner.y))
				return false;
			if(with_check_transparency && this->texture)
			{
				auto self_img = get_texture()->copyToImage();
				sf::Sprite some_sprite = Sprite(*texture::pixel.get_texture());
				some_sprite.setPosition(cords.x, cords.y);
				sf::Image some_img = texture::pixel.get_texture()->copyToImage();
				return helping_function::PixelPerfectCollision(this->sprite, some_sprite, self_img, some_img);
			}
			return true;
        }

        virtual int bind_mouse_in(event_function_type function, observer_list& observer)
        {
            mouse_in_function = function;
            return observer.bind(sf::Event::MouseMoved, [this](sf::Event event) {
                return this->mouse_in(event);
            }, this);
        }
		virtual int bind_mouse_out(event_function_type function, observer_list& observer)
        {
            mouse_out_function = function;
			if(!mouse_in_function)
				return bind_mouse_in([](sf::Event event){return false; }, observer);
        }
    };
}}
