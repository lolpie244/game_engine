//
// Created by lolpie on 11/19/21.
//
#pragma once
#include "../mixins/includes.h"
#include "../../helping/structs.h"
namespace objects{ namespace gui
{
    using mixins::Clickable, mixins::Scalable, mixins::Drawable1;
    using structs::Point;
    using parent::object_constructor;
    using texture::common_texture;

    class gui_object: public object_constructor, public Clickable, public Scalable, public Drawable1
    {
    public:
        gui_object() = default;


        gui_object(Point position, Point size, sh_p<common_texture> new_texture):
                object_constructor(position, size, new_texture){}

    };
}}
