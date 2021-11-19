//
// Created by lolpie on 11/19/21.
//



namespace object_parameters
{
    using namespace sf;
    class common_draw : virtual public objects::parent_object, public Drawable
    {
    public:
        void draw(RenderTarget& target, RenderStates states) const
        {
            target.draw(sprite, states);
        }

    };
}