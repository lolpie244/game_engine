//
// Created by lolpie on 11/19/21.
//

namespace info
{
    using namespace sf;
    using namespace std;
    class parent
    {
    public:
    };
    class render : public parent
    {
    public:
        sh_p<RenderWindow> window;
        chrono::system_clock::time_point time_point;

        render(sh_p<RenderWindow> new_window)
        {
            window = new_window;
            time_point = std::chrono::system_clock::now();
        }
    };
    class gui : public parent
    {
    public:
        vector<sh_p<objects::gui_object>> objects;
        event::observer_list observer_list;
        void draw(sf::RenderWindow& window)
        {
            for(auto obj: objects)
            {
                window.draw(*obj);
            }
        }
    };
}
