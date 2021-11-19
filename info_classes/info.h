//
// Created by lolpie on 11/19/21.
//

namespace info
{
    using namespace sf;
    using namespace std;
    class parent
    {

    };
    class render : public parent
    {
    public:
        shared_ptr<RenderWindow> window;
        chrono::system_clock::time_point time_point;

        render(RenderWindow* new_window)
        {
            window = shared_ptr<RenderWindow>(new_window);
            time_point = std::chrono::system_clock::now();
        }
    };
}
