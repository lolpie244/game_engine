//
// Created by lolpie on 10/20/22.
//

namespace mixins
{
    using sf::RenderStates, sf::RenderTarget;
    using parent::object;

    class common_draw
    {
    public:
        virtual void draw(RenderTarget &target, RenderStates states, const object* obj)
        {
            target.draw(obj->get_const_sprite(), states);
        }
    };

    class Drawable: virtual public object, public sf::Drawable
    {
        sh_p<common_draw> draw_obj = sh_p<common_draw>(new common_draw());
    public:
        void draw(RenderTarget& target, RenderStates states) const override
        {
            if(is_active)
                draw_obj->draw(target, states, this);
        }
        void set_draw(sh_p<common_draw> obj)
        {
            draw_obj = std::move(obj);
        }
    };


}