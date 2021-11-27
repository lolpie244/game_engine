//
// Created by lolpie on 11/19/21.
//

namespace objects
{
    class gui_objects : public object
    {
    public:
        template<typename T, typename P>
        gui_objects(shared_ptr<Texture>& new_texture, Rect<float> rect, T* scale, P* draw):
                object(new_texture, rect, scale, draw){}

    };
    class text_object : public parent_object
    {
        sf::Text text;
        sh_p<Font> font;
    public:
        Text& get_text()
        {
            return this->text;
        }
        void update_text()
        {
            text.setOrigin(text.getLocalBounds().width / 2.0, text.getLocalBounds().height * 2);
            text.setPosition(this->get_position());
            text.setScale(sprite.getScale());
        }
        template<typename T, typename P>
        text_object(Rect<float> rect, string new_text, int letter_size, sh_p<Font>& font, Color color)
        {
            this->text.setFillColor(color);
            this->font = font;
            text.setFont(*font);
            text.setString(new_text);
            text.setCharacterSize(letter_size);
            update_text();
        }
    };
    class button : public gui_objects
    {
        sh_p<sf::Texture> pressed_texture;
        sh_p<sf::Texture> unpressed_texture;
    public:
        template<typename T, typename P>
        button(shared_ptr<Texture>& new_texture, shared_ptr<Texture>& new_pressed_texture, Rect<float> rect,
                    T* scale, P* draw):
            gui_objects(new_texture, rect, scale, draw)
        {
            this->pressed_texture = new_pressed_texture;
            this->unpressed_texture = texture;
        }
        void pressed()
        {
            update_texture(pressed_texture);
        }
        void unpressed()
        {
            update_texture(unpressed_texture);
        }
    };
}
