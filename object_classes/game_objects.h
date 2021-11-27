//
// Created by lolpie on 14.11.21.
//


namespace objects
{
    class game_objects : public object
    {
    public:
        template<typename T, typename P>
        game_objects(shared_ptr<Texture> new_texture, Rect<float> rect, T* scale, P* draw):
                object(new_texture, rect, scale, draw){}

    };

}