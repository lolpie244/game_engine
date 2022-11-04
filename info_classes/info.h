//
// Created by lolpie on 11/19/21.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include "../objects/mixins/includes.h"
namespace info
{
    using namespace sf;
    using namespace std;
    using objects::mixins::BaseDrawable, objects::mixins::BaseScalable;

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
            bool operator()(const objects::parent::abstract_object* first, const objects::parent::abstract_object* second) const
            {
                if(first->get_position().z != second->get_position().z)
                    return first->get_position().z < second->get_position().z;
                return *first < *second;
            }
        };


        sh_p<RenderWindow> window;
        set<BaseDrawable*, DepthCompare> objects_to_draw;
    public:

        stage_elements(sh_p<RenderWindow> window)
        {
            this->window = window;
        }
        stage_elements(){}
        events::observer_list event_manager;
        void draw()
        {
            for(auto obj: objects_to_draw)
                window->draw(*obj);
        }

        void push_back(objects::parent::abstract_object* obj)
        {
            auto scale_casted = dynamic_cast<BaseScalable*>(obj);
            if(scale_casted)
			{
                scale_casted->bind_scale(window, event_manager);
				auto win = window->getSize();
				window->setSize({win.x + 1, win.y});
				window->setSize({win.x, win.y});
			}
            auto draw_casted = dynamic_cast<BaseDrawable*>(obj);
            if(draw_casted)
                objects_to_draw.insert(draw_casted);
        }
        void insert(initializer_list<objects::parent::abstract_object*> obj)
        {
            list<objects::parent::abstract_object*> obj_list = obj;
            insert(obj_list);
        }
        void insert(list<objects::parent::abstract_object*> obj)
        {
            for(auto to_add: obj)
            	this->push_back(to_add);
        }
        void remove_object(objects::parent::abstract_object* obj)
        {
            event_manager.unbind_all(obj);

            auto to_erase = dynamic_cast<BaseDrawable*>(obj);
            if(to_erase)
                objects_to_draw.erase(to_erase);
        }
    };
}
