#include <utility>

//
// Created by lolpie on 11/23/21.
//

namespace objects_np
{
    using namespace events;
    using namespace structs;
    class object : public parent_object
    {
    public:
        map<int, int> Events;
        shared_ptr<object_parameters::none_scale> scale_obj;
        shared_ptr<object_parameters::common_draw> draw_obj;
        shared_ptr<object_parameters::static_move> move_obj;
        object() = default;
        Point speed = {0, 0};
        template<typename ScaleT, typename DrawT, typename MoveT>
        object(shared_ptr<Texture>& new_texture, Rect<float> rect, ScaleT* scale, DrawT* draw, MoveT* move, vector<Point> points={})
        {
            this->scale_obj = shared_ptr<ScaleT>(scale);
            this->draw_obj = shared_ptr<DrawT>(draw);
            this->move_obj = shared_ptr<MoveT>(move);

            this->points = std::move(points);
            this->sprite = Sprite();
            this->update_texture(new_texture);
            this->sprite.setPosition(rect.left, rect.top);
            this->sprite.setScale(rect.width, rect.height);
        }
        bool button_click(Vector2<float> cords)
        {
            auto self_img = this->texture->copyToImage();
            sf::Sprite some_sprite = Sprite(*pre_loaded::pixel.get());
            some_sprite.setPosition(cords.x, cords.y);
            sf::Image some_img = pre_loaded::pixel.get()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_sprite, self_img, some_img);
        }
        virtual bool scale(Window& window)
        {
            if(is_active)
                scale_obj->scale(this->sprite, this->points, window);
        }
        virtual void draw(RenderTarget& target, RenderStates states) const
        {
            if(is_active)
                draw_obj->draw(target, states, this->sprite, *this->texture);
        }
        virtual void move()
        {
            if(is_active)
                move_obj->move(this->sprite, speed);
        }

    };


}