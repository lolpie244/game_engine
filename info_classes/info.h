//
// Created by lolpie on 11/19/21.
//

namespace info
{
    using namespace sf;
    using namespace std;

    template <typename T, typename Map, typename Field>
    sh_p<T> get_info(Map& container, const Field& field)
    {
        return static_pointer_cast<T>(container[field]);
    }
    class parent
    {
    public:
    };
    class render : public parent
    {
    public:
        sh_p<RenderWindow> window;
        chrono::system_clock::time_point time_point;
        event::observer_list event_manager;
        render(sh_p<RenderWindow> new_window)
        {
            window = new_window;
            time_point = std::chrono::system_clock::now();
        }
    };
    class gui : public parent
    {
    public:
        vector<sh_p<objects::gui_objects>> objects;
        event::observer_list event_manager;
        void draw(sf::RenderWindow& window)
        {
            for(auto obj: objects)
                window.draw(*obj);
        }
    };
}
