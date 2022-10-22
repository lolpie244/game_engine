//
// Created by lolpie on 11/19/21.
//

namespace gui
{
    using mixins::Clickable, mixins::Scalable, mixins::Drawable;
    using sf::Texture, std::initializer_list, helping_function::Point;
    using parent::object, parent::object_constructor;
    using texture::common_texture;

    class gui_object: public object_constructor, public Clickable, public Scalable, public Drawable
    {
    public:
        gui_object() = default;


        gui_object(Point position, Point size, sh_p<common_texture> new_texture):
                object_constructor(position, size, new_texture){}

    };

}
