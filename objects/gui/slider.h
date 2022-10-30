//
// Created by lolpie on 10/21/22.
//
#pragma once
#include "../mixins/includes.h"
#include "../../helping/structs.h"
#include "../parent/includes.h"
#include "../mixins/includes.h"
#include "../../event/observer_object.h"
// #include <SFML/Graphics/Drawable.hpp>

namespace objects{ namespace gui
{
    using mixins::Draggable, mixins::CompositeScalable;
    using parent::composite_object, parent::object_constructor;
	using mixins::Drawable, mixins::Drawable1, mixins::Scalable, mixins::Clickable;
    using structs::Point;

    class Slider: public CompositeScalable, public Drawable
    {

        class Base : public object_constructor, public Drawable, public Scalable, public Clickable
        {
        public:
            Base()= default;

            Base(Point position, Point size, sh_p<texture::common_texture> new_texture) :
                    object_constructor(position, size, new_texture) {}
        };

        class Picker : public object_constructor, public Drawable, public Scalable, public Draggable
        {
        public:
            Picker()= default;

            Picker(Point position, Point size, sh_p<texture::common_texture> new_texture) :
                    object_constructor(position, size, new_texture) {

            }
        };

        void update_value()
        {
            Point current_position = picker.get_position();
            double temp_value = current_position.x - picker_segment_points.first.x;
            double len = get_segment_len().x;
            this->value = (temp_value / len) * (max_value - min_value);
        }
        void update_picker_cord()
        {
            picker.set_x_position(value / (max_value - min_value) * get_segment_len().x + picker_segment_points.first.x);
        }

        sh_p<texture::slider> picker_texture;

        std::pair<Point, Point> picker_segment_points;
        double value = 0;
        double min_value = 0;
        double max_value = 10;

        Point get_segment_len()
        {
            return picker_segment_points.second - picker_segment_points.first;
        }
        void update_value_by_cord(Point new_pos)
        {
            if(picker_segment_points.first.x <= new_pos.x && new_pos.x <= picker_segment_points.second.x)
            {
                this->picker.set_x_position(new_pos.x);
                update_value();
            }
        }

    public:
        Base slider;
        Picker picker;

        std::list<objects::parent::object*> get_objects() override
        {
            return {&slider, &picker};
        }
        std::list<Point*> get_points_to_scale() override
        {
            return {&picker_segment_points.first, &picker_segment_points.second};
        }
        double get_value()
        {
            return value;
        }
        double set_value(double new_value)
        {
            value = std::max(std::min(new_value, max_value), min_value);
            update_picker_cord();
        }

        Slider()
        {
            set_after_scale([this](sf::Event event){
                this->update_picker_cord();
                return false;
            });
        }
        Slider(Point position, Point slider_size, sh_p<texture::slider> new_texture)
        {

            picker_texture = new_texture;
            slider = Base(position, slider_size, new_texture->get_slider());
            picker = Picker(
                    {0, 0},
                    Point(picker_texture->get_picker()->get_texture()->getSize()) * slider.get_texture_scale(),
                    picker_texture->get_picker());

            update_slider_texture(new_texture);
            Point picker_position = picker_segment_points.first;
            picker_position.z = slider.get_position().z + 0.1;

            picker.set_position(picker_position);
        }
        void update_slider_texture(sh_p<texture::slider> new_texture)
        {
            picker_texture = new_texture;
            picker.update_texture(new_texture->get_picker());
            slider.update_texture(new_texture->get_slider());

            auto slider_point = &slider;
            auto lam = [slider_point](Point point){
                return (slider_point->get_left_corner() + point * slider_point->get_texture_scale());
            };
            picker_segment_points = {
                    lam(picker_texture->get_picker_segment().first), lam(picker_texture->get_picker_segment().second)
            };
            update_picker_cord();

        }

        void bind_slider(event_function_type function, events::observer_list& observer)
        {
            picker.bind_drag([this, function](sf::Event event){
                update_value_by_cord(this->picker.get_position() + Point(this->picker.get_moved_to().x, 0));
                function(event);
                return true;
            }, observer);

            slider.bind_press([this, function](sf::Event event){
                update_value_by_cord(Point(event.mouseButton.x, 0));
                function(event);
                return true;
                }, observer);
            set_after_scale([this](sf::Event event){
                this->update_picker_cord();
                return false;
            });
        }
    };
}}
