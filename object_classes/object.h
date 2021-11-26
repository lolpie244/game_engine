//
// Created by lolpie on 11/23/21.
//

namespace objects
{
    class object : public parent_object, public Drawable
    {
    public:
        shared_ptr<object_parameters::none_scale> scale_obj;
        shared_ptr<object_parameters::common_draw> draw_obj;
        object()= default;
        template<typename T, typename P>
        object(shared_ptr<Texture>& new_texture, Rect<float> rect, T* scale, P* draw)
        {
            this->scale_obj = shared_ptr<T>(scale);
            this->draw_obj = shared_ptr<P>(draw);

            this->texture = new_texture;
            this->sprite = Sprite(*this->texture);
            auto size = this->get_size();
            this->sprite.setOrigin(size.x / 2.0, size.y / 2.0);
            this->sprite.setPosition(rect.left, rect.top);
            this->sprite.setScale(rect.width, rect.height);
        }
        bool button_click(Vector2<float> cords)
        {
            auto self_img = this->texture->copyToImage();
            sf::Sprite some_sprite = Sprite(*textures::pixel.get());
            some_sprite.setPosition(cords.x, cords.y);
            sf::Image some_img = textures::pixel.get()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_sprite, self_img, some_img);
        }
        bool object_collision(object* some_obj)
        {
            sf::Image self_img = this->texture->copyToImage();
            sf::Image some_img = some_obj->get_texture()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_obj->get_sprite(), self_img, some_img);
        }
        void scale(Window& window)
        {
            scale_obj->scale(this->sprite, window);
        }
        void draw(RenderTarget& target, RenderStates states) const
        {
            draw_obj->draw(target, states, this->sprite, *this->texture);
        }

    };


}