//
// Created by lolpie on 14.11.21.
//


namespace object_parameters
{
    using namespace helping_function;
    using namespace sf;
    class none_scale
    {
    protected:
        Point old_scale;
    public:
        none_scale()
        {
            old_scale = {1, 1};
        }
        virtual void scale(Sprite& sprite, vector<Point>& points, Window& window)
        {
        }
    };

    class full_scale : virtual public none_scale
    {
    public:
        void scale(Sprite& sprite, vector<Point>& points, Window& window) override
        {
            auto size = get_window_scale(window);
            auto scale = sprite.getScale();
            float min_ = std::min(size.x, size.y);
            float old_min = std::min(old_scale.x, old_scale.y);
            sprite.setScale(scale.x / old_min * min_, scale.y / old_min * min_);

            sprite.setPosition(sprite.getPosition().x * size.x / old_scale.x, sprite.getPosition().y * size.y / old_scale.y);
            for(Point& point : points)
                point = point * (min_ / old_min);

            old_scale = size;
        }
    };

    class coord_scale : virtual public none_scale {
    public:
        void scale(Sprite& sprite, vector<Point>& points, Window& window) override
        {
            auto size = get_window_scale(window);
            Point position_scale = {size.x / old_scale.x, size.y / old_scale.y};
            sprite.setPosition(sprite.getPosition().x * (float)position_scale.x, sprite.getPosition().y * (float)position_scale.y);
            for(Point& point : points)
                point = point * position_scale;
            old_scale = size;
        }
    };

}