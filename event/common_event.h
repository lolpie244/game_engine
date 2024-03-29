//
// Created by lolpie on 11/25/21.
//
#pragma once
#include <utility>
#include "../objects/parent/includes.h"
#include "observer_object.h"

namespace events
{
    using namespace std;
    using objects::parent::object;

    template<typename T_obj>
    class event
    {
    protected:
        T_obj* obj;
    public:
        event(T_obj* new_obj)
        {
            obj = new_obj;
        }
        void add_to_observer(observer_list& observer){}
    };
}
