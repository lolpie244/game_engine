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
            this->scale_obj = shared_ptr<T>();
            this->draw_obj = shared_ptr<P>(draw);

            this->texture = new_texture;
            this->sprite = Sprite(*this->texture);
            auto size = this->get_size();
            this->sprite.setOrigin(size.x / 2.0, size.y / 2.0);
            this->sprite.setPosition(rect.left, rect.top);
            this->sprite.setScale(rect.width, rect.height);
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