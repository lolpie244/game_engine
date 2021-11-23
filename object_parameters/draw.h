//
// Created by lolpie on 11/19/21.
//



namespace object_parameters
{
    using namespace sf;
    class common_draw
    {
    public:
        void draw(RenderTarget& target, RenderStates states, Sprite sprite, Texture& texture) const
        {
            target.draw(sprite, states);
        }

    };
}