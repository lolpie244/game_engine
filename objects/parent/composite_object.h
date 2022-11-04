//
// Created by lolpie on 10/22/22.
//
#pragma once
#include <list>
#include <vector>
#include "abstract_object.h"
#include "object.h"

namespace objects { namespace parent
{
    using std::list, std::vector;
    class composite_object: virtual public abstract_object
    {
    public:
        composite_object()=default;
        virtual list<object*> get_objects()
		{
			return {};
		}
        virtual list<object*> get_const_objects() const
		{
			return const_cast<composite_object*>(this)->get_objects();
		}
		virtual vector<Point*> get_points()
		{
			return {};
		}
        virtual vector<Point*> get_points() const
		{
			return const_cast<composite_object*>(this)->get_points();
		}

        template<typename T>
        list<T*> get_objects() const
        {
			return const_cast<composite_object*>(this)->get_objects<T>();
        }
		template<typename T>
        list<T*> get_objects()
        {
            list<T*> result;
            for(auto obj: get_objects())
            {
                auto casted = dynamic_cast<T*>(obj);
                if(casted)
                    result.push_back(casted);
            }
            return result;
        }
        virtual ~composite_object()=default;
    };
}}
