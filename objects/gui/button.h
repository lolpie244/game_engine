//
// Created by lolpie on 10/20/22.
//

namespace gui
{
    class button : public gui_object
    {
        sh_p<sf::Texture> pressed_texture;
        sh_p<sf::Texture> released_texture;
    public:
        button(){}
        button(initializer_list<Point> points, Point position,
               sh_p<Texture>& released_texture, sh_p<Texture>& pressed_texture):
                gui_object(points, position, released_texture)
        {
            this->pressed_texture = pressed_texture;
            this->released_texture = released_texture;
        }
        void set_textures(sh_p<Texture>& new_released_texture, sh_p<Texture>& new_pressed_texture, bool is_pressed=false)
        {
            this->pressed_texture = new_pressed_texture;
            this->released_texture = new_released_texture;
            if(is_pressed)
                pressed();
            else
                unpressed();
        }
        void pressed()
        {
            update_texture(pressed_texture);
        }
        void unpressed()
        {
            update_texture(released_texture);
        }
    };
}