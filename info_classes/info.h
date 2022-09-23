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
    class parent{};
    class render : public parent
    {
    public:
        sh_p<RenderWindow> window;
        chrono::system_clock::time_point time_point;
        events::observer_list event_manager;
        render(sh_p<RenderWindow> new_window)
        {
            window = new_window;
            time_point = std::chrono::system_clock::now();
        }
    };

    class stage_elements : public parent
    {
        sh_p<RenderWindow> window;
    public:
        vector<objects_np::object*> objects;
        stage_elements(sh_p<RenderWindow> window)
        {
            this->window = window;
        }
        stage_elements(){}
        events::observer_list event_manager;
        void draw()
        {
            for(auto obj: objects)
                window->draw(*obj);
        }
        void move()
        {
            for(auto obj : objects)
                obj->move();
        }
        void push_back(objects_np::object* obj, bool with_scale=true)
        {
            objects.push_back(obj);
            if(with_scale)
            {
                obj->scale(*window);
                new events::scale(obj, window, event_manager);
            }
        }
        void insert(initializer_list<objects_np::object*> obj, bool with_scale=true)
        {
            objects.insert(objects.end(), obj);
            if(with_scale)
                for(auto i : obj)
                {
                    i->scale(*window);
                    new events::scale(i, window, event_manager);
                }
        }
    };
}
