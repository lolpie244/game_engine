//
// Created by lolpie on 10/21/22.
//
#pragma once
#include "class.h"
#include <iostream>


namespace objects{ namespace mixins
{
	using std::min;
    class relative_position_scale : virtual public none_scale
    {
    public:
        void scale(Window& window, Scalable* obj) override
        {
            auto size = get_window_scale(window);
            auto scale = obj->get_sprite().getScale();

            double min_ = min(size.x, size.y);
            double old_min = min(old_scale.x, old_scale.y);

            double current_scale = min_ / old_min;
            obj->get_sprite().setScale(scale.x * current_scale, scale.y * current_scale);

            obj->set_position(obj->get_position() * current_scale);

            old_scale = size;
        }
    };
    class attach_position_scale : virtual public none_scale
    {
    public:
        void scale(Window& window, Scalable* obj) override
        {
            auto size = get_window_scale(window);
            auto scale = obj->get_sprite().getScale();

            double min_ = min(size.x, size.y);
            double old_min = min(old_scale.x, old_scale.y);


            obj->get_sprite().setScale(scale.x / old_min * min_, scale.y / old_min * min_);

            Point position_scale = {size.x / old_scale.x, size.y / old_scale.y};

            Point center = obj->get_position();
            obj->set_position(center * position_scale);

            for(auto& point: obj->points)
                point = point * position_scale;

            old_scale = size;
        }
    };

    class coord_scale_2d : virtual public none_scale
    {
    public:
        void scale(Window& window, Scalable* obj) override
        {
            auto size = get_window_scale(window);
            Point center = obj->get_position();

            Point position_scale = {size.x / old_scale.x, size.y / old_scale.y};

            obj->set_position(center * position_scale);
            for(auto& point: obj->points)
                point = point * position_scale;
            old_scale = size;
        }
    };

    class composite_attach_scale : virtual public none_scale_composite
    {
    public:
        void scale(Window& window, CompositeScalable* obj) override
        {
			auto size = get_window_scale(window);

            double min_ = min(size.x, size.y);
            double old_min = min(old_scale.x, old_scale.y);

            Point position_scale = {size.x / old_scale.x, size.y / old_scale.y};
			if(min_ / old_min == 1)
				if(min_ == size.y && old_min == old_scale.y)
				{
					std::cout << size.x - old_scale.x <<  '\n';
					position_scale.x *= old_scale.x / size.x;
					old_scale = size;
					return;
					// position_scale += 
				}
            for(Point* point: obj->get_points())
                *point = *point * position_scale;

            old_scale = size;
		}
    };
    class composite_relative_scale : virtual public none_scale_composite
    {
    public:
        void scale(Window& window, CompositeScalable* obj) override
        {
            auto size = get_window_scale(window);
            double min_ = min(size.x, size.y);
            double old_min = min(old_scale.x, old_scale.y);

            double position_scale = min_ / old_min;

            for(Point* point: obj->get_points())
                *point = *point * position_scale;

            old_scale = size;
        }
    };
}}
