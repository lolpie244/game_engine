//
// Created by lolpie on 14.11.21.
//


namespace figures
{
    using mixins::Clickable, mixins::Scalable, mixins::Drawable, mixins::Movable;
    using sf::Texture, std::initializer_list, helping_function::Point;
    using parent::object;

    class figure_object: public Clickable, public Scalable, public Drawable, public Movable
    {
    public:
        figure_object()= default;


        figure_object(initializer_list<Point> points, Point position, sh_p<Texture>& new_texture):
                object(points, position, new_texture){}

    };

}