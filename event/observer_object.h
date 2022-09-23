//
// Created by lolpie on 11/25/21.
//

namespace events
{
    using namespace std;
    class observer_list
    {
        class observer_object
        {
            struct parent_func
            {
                virtual bool run(sf::Event sfml_event){}
            };
            template<typename T>
            struct func_struct : parent_func
            {
                shared_ptr<T> func;
                func_struct(sh_p<T> new_func)
                {
                    func = new_func;
                }
                bool run(sf::Event sfml_event)
                {
                    return (*func)(sfml_event);
                }
            };
        public:

            vector<sh_p<parent_func>> func_list;
            template<typename T>
            void add_func(T A, int pos=-1)
            {
                if(pos == -1)
                    func_list.emplace_back(new func_struct(A));
                else
                    func_list[pos] = sh_p<parent_func>(new func_struct(A));
            }
            void notify(sf::Event sfml_event)
            {

                for(auto i: func_list)
                {
                    if(i->run(sfml_event))
                        return;
                }
            }

        };
        map<int, observer_object> list_;
    public:
        observer_object& notify(sf::Event event)
        {
            list_[event.type].notify(event);
        }
        template<typename T_temp_func, typename T_func=function<bool(sf::Event)>>
        void bind_event(int event, T_temp_func new_func, objects_np::object* obj = nullptr)
        {
            auto temp_func = new T_func(new_func);
            int id = -1;
            if(obj != nullptr)
                if(obj->Events.contains(event))
                    id = obj->Events[event];
                else
                    obj->Events[event] = list_[event].func_list.size();

            list_[event].add_func(shared_ptr<T_func>(temp_func), id);
        }
        void remove_event(int event, int id)
        {
            list_[event].func_list.erase(list_[event].func_list.begin() + id);
        }
        void remove_event(int event, objects_np::object* obj)
        {
            if(!obj->Events.contains(event))
                return;
            int event_id = obj->Events[event];
            list_[event].func_list.erase(list_[event].func_list.begin() + event);
            obj->Events.erase(event);
        }
    };
}
