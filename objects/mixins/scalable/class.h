//
// Created by lolpie on 10/20/22.
//
#pragma once
#include <SFML/Window.hpp>
#include "../../../helping/includes.h"
#include "../../../helping/structs.h"
#include "../../../event/observer_object.h"


namespace objects{ namespace mixins
{
    using sf::Window;
    using helping_function::get_window_scale, structs::Point;
    using std::list;
    using events::observer_list;
    using parent::object, parent::composite_object;

    class BaseScalable: virtual public objects::parent::abstract_object
    {
    protected:
        event_function_type after_scale;
    public:
		virtual int bind_scale(sh_p<sf::RenderWindow> window, observer_list& observer){}
        void set_after_scale(const event_function_type&  new_after_scale)
        {
            this->after_scale = new_after_scale;
        }
        virtual void scale(Window& window) {}
    };


    class Scalable;

    class none_scale
    {
    protected:
        Point old_scale;
    public:
        none_scale()
        {
            old_scale = {1, 1, 1};
        }

        virtual void scale(Window &window, Scalable* obj) {}
    };
    class Scalable: virtual public parent::object, public BaseScalable
    {
    protected:
        sh_p<none_scale> scale_obj = sh_p<none_scale>(new none_scale());
    public:

        template <typename Type>
        void set_scale()
        {
            scale_obj = sh_p<none_scale>(new Type());
        }

        void scale(Window& window) override
        {
            scale_obj->scale(window, this);
        }
        int bind_scale(sh_p<sf::RenderWindow> window, observer_list& observer) override
        {
            scale(*window);
            return observer.bind(sf::Event::Resized, [this, window](sf::Event event) {
                this->scale(*window);
                if(after_scale)
                    this->after_scale(event);
                return false;
            }, this);
        }
        template <typename Type>
        int bind_scale(sh_p<sf::RenderWindow> window, observer_list& observer)
        {
            set_scale<Type>();
            bind_scale(window, observer);
        }
    };

    class CompositeScalable;

    class none_scale_composite
    {
    protected:
        Point old_scale;
    public:
        none_scale_composite()
        {
            old_scale = {1, 1, 1};
        }

        virtual void scale(Window &window, CompositeScalable* obj) {}
    };

    class CompositeScalable: public BaseScalable, virtual public composite_object
    {
        sh_p<none_scale_composite> scale_obj = sh_p<none_scale_composite>(new none_scale_composite());
    public:
        virtual list<Point*> get_points_to_scale(){}

        virtual void scale(Window& window) override
        {
            scale_obj->scale(window, this);
        }
        virtual int bind_scale(sh_p<sf::RenderWindow> window, observer_list& observer) override
        {
            scale(*window);
            return observer.bind(sf::Event::Resized, [this, window](sf::Event event) {
                this->scale(*window);
                this->after_scale(event);
                return false;
            }, this);
        }
        template <typename T_obj, typename T_compos>
        int bind_scale(sh_p<sf::RenderWindow> window, observer_list& observer)
        {
            for(auto objects: this->get_objects<Scalable>())
                objects->bind_scale<T_obj>(window, observer);
            scale_obj = sh_p<none_scale_composite>(new T_compos());
            bind_scale(window, observer);
        }
    };
}}
