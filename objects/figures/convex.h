namespace figures
{
//    using namespace structs;
//    class convex : public object
//    {
//    public:
//        vector<structs::Point> points;
//        vector<vector<structs::Point>> convex_points;
//
//        Color color;
//        convex() = default;
//        template<typename DrawT, typename ScaleT, typename MoveT>
//        convex(vector<Point> points, ScaleT* scale, DrawT* draw, MoveT* move, Color color = Color::Green)
//        {
//            this->scale_obj = shared_ptr<ScaleT>(scale);
//            this->draw_obj = shared_ptr<DrawT>(draw);
//            this->move_obj = shared_ptr<MoveT>(move);
//            this->color = color;
//            this->points = std::move(points);
//        }
//        void update_concave_to_convex()
//        {
//            convex_points = helping_function::concave_to_convexes(points);
//        }
//        template<typename T, typename P>
//        convex(vector<Point> points, shared_ptr<Texture>& new_texture, T* scale, P* draw, int depth = 0):
//                convex(points, scale, draw)
//        {
//            this->update_texture(texture);
//        }
//        virtual bool scale(Window& window) override
//        {
//            if(is_active)
//                scale_obj->scale(this->sprite, this->points, window);
//            return false;
//        }
//        virtual void draw(RenderTarget& target, RenderStates states) const override
//        {
//            if(is_active)
//                draw_obj->draw(target, states, this->points, color);
//        }
//        virtual void move() override
//        {
//            if(is_active)
//                move_obj->move(this->points, this->convex_points, speed);
//        }
//    };


}