//
// Created by lolpie on 11/25/21.
//

namespace event
{
    using namespace std;
    template<typename T_obj>
    class event
    {
    protected:
        sh_p<T_obj> obj;
    public:
        event(sh_p<T_obj> new_obj)
        {
            obj = new_obj;
        }
        template<typename T>
        void add_to_observer(T& observer)
        {
            observer.bind_event(sf::Event::Resized, [this](sf::Event event){this->do_scale(event);});
        }
    };

    template<typename T_obj, typename T_temp_func,
            typename T_released_func=function<void()>, typename T_press_func=function<void()>>
    class button : public event<T_obj>
    {
    protected:
        bool is_pressed = false;
        sh_p<T_released_func> release_function;
        sh_p<T_press_func> press_function;
    public:
        button(sh_p<T_obj> new_obj, T_temp_func new_release_func, T_press_func new_press_function = [](){}):
            event<T_obj>(new_obj)
        {
            this->release_function = shared_ptr<T_released_func>(new T_released_func(new_release_func));
            this->press_function = shared_ptr<T_press_func>(new T_press_func(new_press_function));
        }

        template<typename T_observer>
        button(sh_p<T_obj> new_obj, T_temp_func new_func, T_press_func new_press_function, T_observer& observer):
                button(new_obj, new_func, new_press_function)
        {
            this->template add_to_observer(observer);
        }
        bool is_mouse_in(sf::Event sfml_event)
        {
            auto obj = this->obj.get();

            return obj->button_click(sf::Vector2<float>(sfml_event.mouseButton.x, sfml_event.mouseButton.y));
        }
        void press(sf::Event sfml_event)
        {
            if(!is_mouse_in(sfml_event))
            {
                is_pressed = false;
                return;
            }
            is_pressed = true;
            (*press_function)();
        }
        void release(sf::Event sfml_event)
        {
            if(!is_mouse_in(sfml_event) or !is_pressed)
                return;
            is_pressed = false;
            (*release_function)();
        }
        template<typename T>
        void add_to_observer(T& observer)
        {
            observer.bind_event(sf::Event::MouseButtonPressed,
                                          [this](sf::Event event){this->press(event);});
            observer.bind_event(sf::Event::MouseButtonReleased,
                                          [this](sf::Event event){this->release(event);});
        }
    };

    template<typename T_obj>
    class scale : event<T_obj>
    {
        sh_p<sf::RenderWindow> window;
    public:
        scale(sh_p<T_obj> new_obj, sh_p<sf::RenderWindow> new_window):
            event<T_obj>(new_obj)
        {
            window = new_window;
        }
        template<typename T_observer>
        scale(sh_p<T_obj> new_obj, sh_p<sf::RenderWindow> new_window, T_observer& observer):
            scale<T_obj>(new_obj, new_window)
        {
            add_to_observer(observer);
        }
        void do_scale(sf::Event sfml_event)
        {
            this->obj->scale(*window);
        }
        template<typename T>
        void add_to_observer(T& observer)
        {
            observer.bind_event(sf::Event::Resized, [this](sf::Event event){this->do_scale(event);});
        }
    };
//    class unpress : event::event
//    {
//
//    };
}