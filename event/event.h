//
// Created by lolpie on 11/25/21.
//

namespace event
{
    using namespace std;
    template<typename T>
    class event
    {
    protected:
        sh_p<T> obj;
    public:
        event(sh_p<T> new_obj)
        {
            obj = new_obj;
        }
    };

    template<typename T_obj, typename T_func>
    class press_button : public event<T_obj>
    {
    protected:
        bool is_pressed = false;
        sh_p<T_func> function;
    public:
        press_button(sh_p<T_obj> new_obj, sh_p<T_func> new_func):
            event<T_obj>(new_obj)
        {
            this->function = new_func;
        }
        bool is_mouse_in(sf::Event sfml_event)
        {
            auto obj = this->obj.get();

            return static_cast<objects::gui_object*>(obj)->
                    button_click(sf::Vector2<float>(sfml_event.mouseButton.x, sfml_event.mouseButton.y));
        }
        void press(sf::Event sfml_event)
        {
            if(!is_mouse_in(sfml_event))
            {
                is_pressed = false;
                return;
            }
            is_pressed = true;
            (*function)();
        }
        void release(sf::Event sfml_event)
        {
            if(!is_mouse_in(sfml_event))
                return;
            is_pressed = false;
            (*function)();
        }
    };
}