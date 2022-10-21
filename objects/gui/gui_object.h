//
// Created by lolpie on 11/19/21.
//

namespace gui
{
    using mixins::Clickable, mixins::Scalable, mixins::Drawable;
    using sf::Texture, std::initializer_list, helping_function::Point;
    using parent::object;

    class gui_object: public Clickable, public Scalable, public Drawable
    {
    public:
        gui_object()= default;


        gui_object(initializer_list<Point> points, Point position, sh_p<Texture>& new_texture):
                object(points, position, new_texture){}

    };
}
