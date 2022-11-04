#pragma once
#include "../../event/observer_object.h"
#include "gui_object.h"

namespace objects{ namespace gui
{
    using events::observer_list;
    class RadioButton : public gui_object
    {
        sh_p<texture::button> button_texture;
    protected:
		bool value = false;
		void sync_texture()
		{
            if(value)
                update_texture(button_texture->get_pressed());
            else
                update_texture(button_texture->get_released());
		}
    public:
        RadioButton(){}
        RadioButton(Point position, Point size, sh_p<texture::button> texture):
                gui_object(position, size, texture->get_released())
        {
            this->button_texture = texture;
        }
		void set_value(bool value)
		{
			this->value = value;
			sync_texture();
		}
		bool get_value()
		{
			return value;
		}
        void set_button_texture(sh_p<texture::button> new_texture, bool is_pressed=false)
        {
            this->button_texture = new_texture;
			sync_texture();
        }
        int bind_press(event_function_type function, observer_list& observer) override
        {
            auto new_function = [this, function](sf::Event event){
				this->value = !this->value;
                this->sync_texture();
                return function(event);
            };
            return Clickable::bind_press(new_function, observer);
        }

    };
}}
