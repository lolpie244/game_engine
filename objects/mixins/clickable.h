//
// Created by lolpie on 10/20/22.
//

namespace mixins
{
    using sf::Vector2, sf::Sprite;
    using helping_function::Point;
    using std::function;
    using events::observer_list;


    class Clickable: virtual public object
    {
    protected:
        event_function_type press_function;
        event_function_type release_function;
        virtual bool press(sf::Event sfml_event)
        {
            if(!is_mouse_in({sfml_event.mouseButton.x, sfml_event.mouseButton.y}))
            {
                is_pressed = false;
                return false;
            }
            is_pressed = true;
            return press_function(sfml_event);

        }
        virtual bool release(sf::Event sfml_event)
        {
            auto old_is_pressed = is_pressed;
            is_pressed = false;
            if(!old_is_pressed || !is_mouse_in({sfml_event.mouseButton.x, sfml_event.mouseButton.y}))
                return false;
            return release_function(sfml_event);

        }
        bool is_pressed = false;
    public:
        bool is_mouse_in(Point cords)
        {
            auto self_img = get_texture()->copyToImage();
            sf::Sprite some_sprite = Sprite(*texture::pixel.get_texture());
            some_sprite.setPosition(cords.x, cords.y);
            sf::Image some_img = texture::pixel.get_texture()->copyToImage();
            return helping_function::PixelPerfectCollision(this->sprite, some_sprite, self_img, some_img);
        }
        virtual int bind_press(event_function_type function, observer_list& observer)
        {
            press_function = function;
            return observer.bind(sf::Event::MouseButtonPressed, [this](sf::Event event) {
                return this->press(event);
            }, this);
        }
        virtual int bind_release(event_function_type function, observer_list& observer)
        {
            release_function = function;
            return observer.bind(sf::Event::MouseButtonReleased, [this](sf::Event event) {
                return this->release(event);
            }, this);
        }

    };
}