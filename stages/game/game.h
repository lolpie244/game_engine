//
// Created by lolpie on 11/19/21.
//
namespace game
{
    using namespace std;
    using namespace sf;
    using namespace parent_stage_class;
    using namespace object_parameters;

    class game: public parent_stage
    {
    private:
        button back_button;
        gui_objects background;
    protected:
        void init_gui_objects() override
        {
            this->gui = info::gui();
            background = gui_objects(pre_loaded::background.get(), Rect<float>(960, 540, 0.5, 0.5),
                                                                    new coord_scale, new common_draw);
            back_button = button(pre_loaded::back.get(), pre_loaded::back_pressed.get(),
                                            Rect<float>(500, 500, 2, 2),new full_scale, new common_draw);
            gui.objects = {&background, &back_button};
        }

        void init_event_objects() override;
    public:
        game(map<string, sh_p<info::parent>>& main_info):
            parent_stage(main_info){}
    };
}
