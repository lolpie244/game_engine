//
// Created by lolpie on 10/20/22.
//

namespace mixins
{
    using sf::Window;
    using helping_function::get_window_scale, helping_function::Point;
    using std::min, std::max;
    using events::observer_list;
    using parent::object;

    class Scalable;

    class none_scale
    {
    protected:
        Point old_scale;
    public:
        none_scale()
        {
            old_scale = {1, 1, 1};
        }

        virtual void scale(Window &window, Scalable* obj) {}
    };
    class Scalable: virtual public object
    {
    protected:
        sh_p<none_scale> scale_obj = sh_p<none_scale>(new none_scale());
    public:

        template <typename Type>
        void set_scale()
        {
            scale_obj = sh_p<none_scale>(new Type());
        }
        void scale(Window& window)
        {
            scale_obj->scale(window, this);
        }
        int bind_scale(sh_p<sf::RenderWindow> window, observer_list& observer)
        {
            scale(*window);
            return observer.bind(sf::Event::Resized, [this, window](sf::Event event) {
                this->scale(*window);
                return false;
            }, this);
        }
        template <typename Type>
        int bind_scale(sh_p<sf::RenderWindow> window, observer_list& observer)
        {
            scale_obj = sh_p<none_scale>(new Type());
            bind_scale(window, observer);
        }
    };
}