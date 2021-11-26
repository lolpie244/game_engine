//
// Created by lolpie on 11/19/21.
//

namespace objects
{
    class gui_object : public object
    {
    public:
        template<typename T, typename P>
        gui_object(shared_ptr<Texture>& new_texture, Rect<float> rect, T* scale, P* draw):
                object(new_texture, rect, scale, draw){}

    };
}
