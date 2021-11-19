//
// Created by lolpie on 11/19/21.
//

namespace objects
{
    template<typename scale_type, typename draw_type>
    class gui_object : virtual public scale_type, virtual public draw_type
    {
        gui_object(shared_ptr<Texture>& new_texture, Rect<float> rect)
        {
            this->texture = new_texture;
            this->sprite = Sprite(*this->texture);
            auto size = this->get_size();
            this->sprite.setOrigin(size.x / 2.0, size.y / 2.0);
            this->sprite.setPosition(rect.left, rect.top);
            this->sprite.setScale(rect.width, rect.height);
        }
        bool button_click(Vector2<float> cords)
        {
            sf::Image self_img = this->texture->copyToImage();
            sf::Sprite some_sprite = Sprite(*textures::pixel.get());
            some_sprite.setPosition(cords.x, cords.y);
            sf::Image some_img = textures::pixel.get()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_sprite, self_img, some_img);
        }
    };
}
