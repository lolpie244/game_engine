//
// Created by lolpie on 10/21/22.
//

namespace mixins
{

    class full_scale_2d : virtual public none_scale
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
}