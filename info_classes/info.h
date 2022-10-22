//
// Created by lolpie on 11/19/21.
//

namespace info
{
    using namespace sf;
    using namespace std;
    using objects::mixins::Drawable, objects::mixins::Scalable;

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
        struct DepthCompare
        {
            bool operator()(const objects::parent::object* first, const objects::parent::object* second) const
            {
                if(first->get_position().z != second->get_position().z)
                    return first->get_position().z < second->get_position().z;
                return first < second;
            }
        };


        sh_p<RenderWindow> window;
        set<Drawable*, DepthCompare> objects;
    public:

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

        void push_back(objects::parent::object* obj)
        {
            auto draw_casted = dynamic_cast<Drawable*>(obj);

            if(draw_casted)
                objects.insert(draw_casted);

            auto scale_casted = dynamic_cast<Scalable*>(obj);
            if(scale_casted)
                scale_casted->bind_scale(window, event_manager);
        }
        void insert(initializer_list<objects::parent::object*> obj)
        {
            list<objects::parent::object*> obj_list = obj;
            insert(obj_list);
        }
        void insert(list<objects::parent::object*> obj)
        {
            for(auto to_add: obj)
            {
                auto draw_casted = dynamic_cast<Drawable*>(to_add);
                if (draw_casted)
                    objects.insert(draw_casted);
            }
            for(auto i : obj)
            {
                auto scale_casted = dynamic_cast<Scalable*>(i);
                if(scale_casted)
                    scale_casted->bind_scale(window, event_manager);
            }
        }
        void remove_object(objects::parent::object* obj)
        {
            event_manager.unbind_all(obj);

            auto to_erase = dynamic_cast<Drawable*>(obj);
            if(to_erase)
                objects.erase(to_erase);
        }
    };
}
