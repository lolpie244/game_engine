#pragma once
#include "SFML/Graphics.hpp"
#include "../../parent/includes.h"
#include "../../../settings/constants_and_defines.h"

namespace objects{ namespace mixins
{
	using sf::RenderStates, sf::RenderTarget;
    using parent::object, parent::composite_object;

	class BaseDrawable: virtual public sf::Drawable, virtual public parent::abstract_object
	{
	public:
		virtual void draw(RenderTarget& target, RenderStates states) const {}
		virtual ~BaseDrawable()=default;
	};

    class ObjectCommonDraw
    {
    public:
        virtual void draw(RenderTarget &target, RenderStates states, const object* obj)
        {
            target.draw(obj->get_const_sprite(), states);
        }
    };

    class Drawable1: virtual public object, public BaseDrawable
	{
        sh_p<ObjectCommonDraw> draw_obj = sh_p<ObjectCommonDraw>(new ObjectCommonDraw());
    public:
        void draw(RenderTarget& target, RenderStates states) const override
        {
            if(is_active)
                draw_obj->draw(target, states, this);
        }
        template <typename Type>
        void set_draw()
        {
            draw_obj = sh_p<ObjectCommonDraw>(new Type());
        }
    };

    class Drawable: virtual public object, public BaseDrawable
	{
        sh_p<ObjectCommonDraw> draw_obj = sh_p<ObjectCommonDraw>(new ObjectCommonDraw());
    public:
        void draw(RenderTarget& target, RenderStates states) const override
        {
            if(is_active)
                draw_obj->draw(target, states, this);
        }
        template <typename Type>
        void set_draw()
        {
            draw_obj = sh_p<ObjectCommonDraw>(new Type());
        }
    };

	class CompositeCommonDraw
	{
	public:
		virtual void draw(RenderTarget &target, RenderStates states, const composite_object* composite_obj)
        {
			for(auto& obj : composite_obj->get_objects<Drawable>())
				target.draw(obj->get_const_sprite(), states);
        }

	};

    class CompositeDrawable: virtual public composite_object, public BaseDrawable
	{
        sh_p<CompositeCommonDraw> draw_obj = sh_p<CompositeCommonDraw>(new CompositeCommonDraw());
    public:
        void draw(RenderTarget& target, RenderStates states) const override
        {
            if(is_active)
                draw_obj->draw(target, states, this);
        }
		template <typename T_obj, typename T_compos>
        void set_draw()
        {
            for(auto objects: this->get_objects<mixins::Drawable>())
                objects->set_draw<T_obj>();
            draw_obj = sh_p<CompositeCommonDraw>(new T_compos());
        }
    };
}}
