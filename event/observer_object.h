//
// Created by lolpie on 11/25/21.
//

namespace event
{
    using namespace std;
    class observer_object
    {
        struct parent_func
        {
            virtual void run(sf::Event sfml_event){}
        };
        template<typename T>
        struct func_struct : parent_func
        {
            shared_ptr<T> func;
            func_struct(sh_p<T> new_func)
            {
                func = new_func;
            }
            void run(sf::Event sfml_event)
            {
                (*func)(sfml_event);
            }
        };
    public:

        vector<sh_p<parent_func>> func_list;
        template<typename T>
        void add_func(T A)
        {
            func_list.emplace_back(new func_struct(A));
        }
        void notify(sf::Event sfml_event)
        {

            for(auto i: func_list)
            {
                i->run(sfml_event);
            }
        }

    };
    class observer_list
    {
        map<int, observer_object> list_;
    public:
        observer_object& get_observer(sf::Event event)
        {
            return list_[event.type];
        }
        observer_object& get_observer(int event)
        {
            return list_[event];
        }
    };
}
