//
// Created by lolpie on 14.11.21.
//


namespace figures
{
    using mixins::Clickable, mixins::Scalable, mixins::Drawable, mixins::Movable;
    using sf::Texture, std::initializer_list, helping_function::Point;
    using parent::object_constructor;

    class figure_object: public object_constructor, public Clickable, public Scalable, public Drawable, public Movable
    {
    public:
        figure_object()= default;


        figure_object(Point position, Point size, sh_p<texture::common_texture> new_texture):
            object_constructor(position, size, new_texture){}

        virtual ~figure_object(){}
    };

}