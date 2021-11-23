//
// Created by lolpie on 14.11.21.
//

namespace object_parameters
{

    using namespace sf;
    class none_scale
    {
    protected:
        Vector2<float> old_scale;
    public:
        none_scale()
        {
            old_scale = Vector2<float>(1, 1);
        }
        virtual void scale(Sprite& sprite, Window& window)
        {
        }
    };

    class full_scale : virtual public none_scale
    {
    public:
        void scale(Sprite& sprite, Window& window) override
        {
            auto size = settings::get_window_scale(window);
            auto scale = sprite.getScale();
            float min_ = std::min(size.x, size.y);
            float old_min = std::min(old_scale.x, old_scale.y);
            sprite.setScale(scale.x / old_min * min_, scale.y / old_min * min_);
            sprite.setPosition(sprite.getPosition().x / old_scale.x * size.x, sprite.getPosition().y / old_scale.y * size.y);
            old_scale = size;
        }
    };

    class coord_scale : virtual public none_scale {
    public:
        void scale(Sprite& sprite, Window& window) override
        {
            auto size = settings::get_window_scale(window);
            sprite.setPosition(sprite.getPosition().x / old_scale.x * size.x, sprite.getPosition().y / old_scale.y * size.y);
            old_scale = size;
        }
    };

}