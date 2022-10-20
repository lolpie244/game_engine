//
// Created by lolpie on 11/19/21.
//

namespace objects_np
{
    class gui_objects : public object
    {
    public:
        gui_objects()= default;

        template<typename ScaleT, typename DrawT, typename MoveT>
        gui_objects(shared_ptr<Texture>& new_texture, Rect<float> rect, ScaleT* scale, DrawT* draw, MoveT* move):
                object(new_texture, rect, scale, draw, move){}

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
        button(){}
        template<typename ScaleT, typename DrawT, typename MoveT>
        button(shared_ptr<Texture>& released_texture, shared_ptr<Texture>& pressed_texture, Rect<float> rect,
               ScaleT* scale, DrawT* draw, MoveT* move):
            gui_objects(released_texture, rect, scale, draw, move)
        {
            this->pressed_texture = pressed_texture;
            this->unpressed_texture = texture;
        }
        void set_textures(shared_ptr<Texture>& new_texture, shared_ptr<Texture>& new_pressed_texture, bool is_pressed=false)
        {
            this->pressed_texture = new_pressed_texture;
            this->unpressed_texture = new_texture;
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
            update_texture(unpressed_texture);
        }
    };
}
