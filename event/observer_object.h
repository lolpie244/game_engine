#include <utility>

//
// Created by lolpie on 11/25/21.
//

namespace events
{
    using namespace std;
    using objects::parent::object;

    class observer_list
    {
        class observer_object
        {
            struct func_struct
            {
                event_function_type func;
                object* obj;
                func_struct(){}
                func_struct(event_function_type new_func, object* new_obj = nullptr)
                {
                    func = std::move(new_func);
                    obj = new_obj;
                }
                bool run(sf::Event sfml_event)
                {
                    if(obj != nullptr && !obj->is_active)
                        return false;
                    return func(sfml_event);
                }
            };
            class DepthCompare
            {
            public:
            bool operator()(const sh_p<func_struct>& first, const sh_p<func_struct>& second) const
            {
                if(second->obj == nullptr && first->obj == nullptr)
                    return first.get() < second.get();
                if(second->obj == nullptr)
                    return true;
                if(first->obj == nullptr)
                    return false;
                if(first->obj->get_position().z != second->obj->get_position().z)
                    return first->obj->get_position().z > second->obj->get_position().z;
                return first.get() < second.get();
            }};

        public:
            int last_event_id = 0;
            unordered_map<object*, int> event_id_by_object;
            map<int, sh_p<func_struct>> event_by_id;
            set<sh_p<func_struct>, DepthCompare> events_set;

            int bind(const event_function_type& new_func, object* obj)
            {
                int event_id = last_event_id++;
                if(obj != nullptr)
                    event_id_by_object[obj] = event_id;
                event_by_id[event_id] = sh_p<func_struct>(new func_struct(new_func, obj));
                events_set.insert(event_by_id[event_id]);
                return event_id;
            }
            void unbind(int event_id)
            {
                events_set.erase(event_by_id[event_id]);
                event_by_id.erase(event_id);
            }
            void unbind(object* obj)
            {
                if(!event_id_by_object.contains(obj))
                    return;

                unbind(event_id_by_object[obj]);
                event_id_by_object.erase(obj);
            }
            void notify(sf::Event sfml_event)
            {
                for(auto& i: events_set)
                    if(i->run(sfml_event))
                        return;
            }

        };
        map<int, observer_object> events;
    public:
        int bind(int event_type, const event_function_type& new_func, object* obj = nullptr)
        {
            return events[event_type].bind(new_func, obj);
        }
        void unbind_all(object* obj)
        {
            for(auto& key_val: events)
                key_val.second.unbind(obj);
        }
        void unbind(int event_type, object* obj)
        {
            events[event_type].unbind(obj);
        }
        void unbind(int event_type, int event_id)
        {
            events[event_type].unbind(event_id);
        }
        void notify(sf::Event sfml_event)
        {
            events[sfml_event.type].notify(sfml_event);
        }

    };
}
