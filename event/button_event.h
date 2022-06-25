

namespace event
{
    template<typename T_obj, typename T_released_func=function<void()>, typename T_press_func=function<void()>>
    class button : public ::event::event<T_obj>
    {
    protected:
        bool is_pressed = false;
        sh_p<T_released_func> release_function;
        sh_p<T_press_func> press_function;
    public:
        button()= default;
        button(T_obj* new_obj, T_press_func new_press_function = [](){}, T_released_func new_release_func=[](){}):
            event<T_obj>(new_obj)
        {
            this->release_function = shared_ptr<T_released_func>(new T_released_func(new_release_func));
            this->press_function = shared_ptr<T_press_func>(new T_press_func(new_press_function));
        }
        template<typename T_observer>
        button(T_obj* new_obj, T_press_func new_press_function, T_released_func new_release_func, T_observer& observer):
                button(new_obj, new_press_function, new_release_func)
        {
            add_to_observer(observer);
        }
        bool is_mouse_in(sf::Event sfml_event)
        {
            auto obj = this->obj;

            return obj->button_click(sf::Vector2<float>(sfml_event.mouseButton.x, sfml_event.mouseButton.y));
        }
        void press(sf::Event sfml_event)
        {
            if(!is_mouse_in(sfml_event))
            {
                is_pressed = false;
                return;
            }
            try
            {
                auto object = dynamic_cast<objects::button *>(this->obj);
                if (object)
                    object->pressed();
            }
            catch (...){}
            is_pressed = true;
            (*press_function)();
        }
        void release(sf::Event sfml_event)
        {
            try
            {
                auto object = dynamic_cast<objects::button *>(this->obj);
                if (object)
                    object->unpressed();
            }
            catch (...){}
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
}