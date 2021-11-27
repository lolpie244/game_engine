//
// Created by lolpie on 11/19/21.
//



namespace object_parameters
{
    using namespace sf;
    class common_draw
    {
    public:
        virtual void draw(RenderTarget& target, RenderStates states, Sprite sprite, Texture& texture) const
        {
            target.draw(sprite, states);
        }
        virtual void draw(RenderTarget& target, RenderStates states, Text text) const
        {
            target.draw(text);
        }
    };
}