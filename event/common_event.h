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
}