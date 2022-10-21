//
// Created by lolpie on 10/20/22.
//

namespace mixins
{
    using sf::Vector2, sf::Sprite;
    class Clickable: virtual public object
    {
        bool button_click(Vector2<float> cords)
        {
            auto self_img = this->texture->copyToImage();
            sf::Sprite some_sprite = Sprite(*pre_loaded::pixel.get());
            some_sprite.setPosition(cords.x, cords.y);
            sf::Image some_img = pre_loaded::pixel.get()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_sprite, self_img, some_img);
        }
    };
}