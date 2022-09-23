#include <utility>

namespace objects_np
{
    using namespace structs;
    class convex_object : public object
    {
    public:
//        shared_ptr<object_parameters::none_scale> scale_obj;
//        shared_ptr<object_parameters::common_draw> draw_obj;

        Color color;
        convex_object() = default;
        template<typename DrawT, typename ScaleT, typename MoveT>
        convex_object(vector<Point> points, ScaleT* scale, DrawT* draw, MoveT* move, Color color = Color::Green)
        {
            this->scale_obj = shared_ptr<ScaleT>(scale);
            this->draw_obj = shared_ptr<DrawT>(draw);
            this->move_obj = shared_ptr<MoveT>(move);
            this->color = color;
            this->points = std::move(points);
        }
        template<typename T, typename P>
        convex_object(vector<Point> points, shared_ptr<Texture>& new_texture,  T* scale, P* draw, int depth = 0):
                convex_object(points, scale, draw)
        {
            this->update_texture(texture);
        }
        bool object_collision(object* some_obj)
        {
            if(this->points.empty() || some_obj->points.empty() || !this->is_active || !some_obj->is_active)
                return false;
            if(this->convex_points.size() == 0)
                this->concave_to_convex();
            if(some_obj->convex_points.size() == 0)
                some_obj->concave_to_convex();
            return helping_function::collision(this->convex_points, some_obj->convex_points);
        }
        virtual bool scale(Window& window) override
        {
            scale_obj->scale(this->sprite, this->points, window);
        }
        virtual void draw(RenderTarget& target, RenderStates states) const override
        {
            draw_obj->draw(target, states, this->points, color);
        }
        virtual void move() override
        {
            if(is_active)
                move_obj->move(this->points, this->convex_points, speed);
        }
    };


}