//
// Created by lolpie on 11/19/21.
//
namespace main_menu_np
{
    using namespace std;
    using namespace sf;
    using namespace parent_stage_class;
    using namespace object_parameters;
    using namespace objects_np;

    class main_menu: public parent_stage
    {
    private:
    protected:
        void init_gui_objects() override
        {
            background = gui_objects(pre_loaded::background.get(), Rect<float>(960, 540, 1, 1),
                                                      new coord_scale, new common_draw, new static_move);
            main_button = objects_np::button(pre_loaded::blue_plus_released.get(), pre_loaded::blue_plus_pressed.get(),
                                 Rect<float>(1775, 950, 1, 1), new full_scale, new common_draw, new static_move);
            elements.insert({&background, &main_button});
        }
        void init_event_objects() override;
        void init_game_objects() override
        {
            convexes = new convex_object[2]{
                convex_object({}, new coord_scale, new common_draw, new convex_move, Color::Blue),
                convex_object({}, new coord_scale, new common_draw, new convex_move, Color::Green)};
            for(int i = 0; i < 2; i++)
                elements.push_back(&convexes[i]);
        }
        void after_events() override
        {
            if(current_convex != 2)
                return;
            if(convexes[0].object_collision(&convexes[1]))
            {
                current_convex = 3;
                for(auto obj: this->elements.objects)
                    obj->speed = {0, 0};
                convexes[0].color = Color::Green;
                return;
            }
//            convexes[0].move();
        }

    public:
        gui_objects background;
        int current_convex = 0;
        convex_object* convexes;
        vector<object*> convexes_points[2];
        objects_np::button main_button;
        main_menu(map<string, sh_p<info::parent>>& main_info):
                parent_stage(main_info){}
    };

}
