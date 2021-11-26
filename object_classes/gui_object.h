//
// Created by lolpie on 11/19/21.
//

namespace objects
{
    class gui_object : public object
    {
    public:
        template<typename T, typename P>
        gui_object(shared_ptr<Texture>& new_texture, Rect<float> rect, T* scale, P* draw):
                object(new_texture, rect, scale, draw){}

        bool button_click(Vector2<float> cords)
        {
            Texture text;
            text.loadFromFile("textures/banner_start_1.png");
            auto self_img = text.copyToImage();
            sf::Sprite some_sprite = Sprite(*textures::pixel.get());
            some_sprite.setPosition(cords.x, cords.y);
            sf::Image some_img = textures::pixel.get()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_sprite, self_img, some_img);
        }
    };
}
