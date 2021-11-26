//
// Created by lolpie on 14.11.21.
//


namespace objects
{
    class game_object : public object
    {
    public:
        template<typename T, typename P>
        game_object(shared_ptr<Texture> new_texture, Rect<float> rect, T* scale, P* draw):
                object(new_texture, rect, scale, draw){}

        bool button_click(Vector2<float> cords)
        {
            sf::Image self_img = this->texture->copyToImage();
            sf::Sprite some_sprite = Sprite(*textures::pixel.get());
            some_sprite.setPosition(cords.x, cords.y);
            sf::Image some_img = textures::pixel.get()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_sprite, self_img, some_img);
        }
        bool object_collision(game_object* some_obj)
        {
            sf::Image self_img = this->texture->copyToImage();
            sf::Image some_img = some_obj->get_texture()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_obj->get_sprite(), self_img, some_img);
        }

    };

}