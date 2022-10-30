//
// Created by lolpie on 10/20/22.
//
#pragma once
#include "../../event/observer_object.h"
#include "gui_object.h"

namespace objects{ namespace gui
{
    using events::observer_list;
    class button : public gui_object
    {
        sh_p<texture::button> button_texture;
    protected:
        bool release(sf::Event sfml_event) override
        {
            if(is_pressed)
                update_texture(button_texture->get_released());
            return Clickable::release(sfml_event);
        }
    public:
        button(){}
        button(Point position, Point size, sh_p<texture::button> texture):
                gui_object(position, size, texture->get_released())
        {
            this->button_texture = texture;
        }
        void set_button_texture(sh_p<texture::button> new_texture, bool is_pressed=false)
        {
            this->button_texture = new_texture;

            if(is_pressed)
                update_texture(button_texture->get_pressed());
            else
                update_texture(button_texture->get_released());
        }
        int bind_press(event_function_type function, observer_list& observer) override
        {
            auto new_function = [this, function](sf::Event event){
                update_texture(button_texture->get_pressed());
                return function(event);
            };
            if(!release_function)
                Clickable::bind_release([](sf::Event event){ return false;}, observer);
            return Clickable::bind_press(new_function, observer);
        }

    };
}}
