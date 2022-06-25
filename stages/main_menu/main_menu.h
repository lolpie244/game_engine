//
// Created by lolpie on 11/19/21.
//
namespace main_menu_np
{
    using namespace std;
    using namespace sf;
    using namespace parent_stage_class;
    using namespace object_parameters;
    using namespace objects;

    class main_menu: public parent_stage
    {
    private:
        button start_button;
        gui_objects flag;
        gui_objects background;
    protected:
        void init_gui_objects() override
        {
            this->gui = info::gui();
            background = gui_objects(pre_loaded::background.get(), Rect<float>(960, 540, 0.5, 0.5),
                                                      new coord_scale, new common_draw);
            start_button = button(pre_loaded::play.get(), pre_loaded::play_pressed.get(),
                                                 Rect<float>(500, 500, 2, 2), new full_scale, new common_draw);
            flag = gui_objects(pre_loaded::banner_start_1.get(), Rect<float>(200, 200, 0.2, 0.2),
                                                      new full_scale, new common_draw);
            gui.objects = {&background, &start_button, &flag};
        }
        void init_event_objects() override;
    public:
        main_menu(map<string, sh_p<info::parent>>& main_info):
                parent_stage(main_info){}
    };

}
