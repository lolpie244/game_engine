//
// Created by lolpie on 14.11.21.
//


namespace objects
{
    template<typename scale_type, typename draw_type>
    class game_object : virtual public scale_type, virtual public draw_type
    {

    public:
        game_object()= default;
        game_object(shared_ptr<Texture>& new_texture, Rect<float> rect)
        {
            this->texture = new_texture;
            this->sprite = Sprite(*this->texture);
            auto size = this->get_size();
            this->sprite.setOrigin(size.x / 2.0, size.y / 2.0);
            this->sprite.setPosition(rect.left, rect.top);
            this->sprite.setScale(rect.width, rect.height);
        }
        bool object_collision(game_object* some_obj)
        {
            sf::Image self_img = this->texture->copyToImage();
            sf::Image some_img = some_obj->get_texture()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_obj->get_sprite(), self_img, some_img);
        }

    };


}