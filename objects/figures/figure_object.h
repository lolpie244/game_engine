//
// Created by lolpie on 14.11.21.
//
#pragma once
#include "../../settings/texture.h"
#include "../../settings/constants_and_defines.h"
#include "../../objects/mixins/includes.h"
#include "../../helping/structs.h"
#include "../../objects/parent/includes.h"

namespace objects::figures
{
    using mixins::Clickable, mixins::Scalable, mixins::Drawable;
    using sf::Texture, std::initializer_list, structs::Point;
    using parent::object_constructor;

    class figure_object: public object_constructor, public Clickable, public Scalable, public Drawable
    {
    public:
        figure_object()= default;


        figure_object(Point position, Point size, sh_p<texture::common_texture> new_texture):
            object_constructor(position, size, new_texture){}

        virtual ~figure_object(){}
    };

}
