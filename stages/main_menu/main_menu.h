//
// Created by lolpie on 11/19/21.
//
namespace main_menu_np
{
    using namespace std;
    using namespace sf;
    using namespace parent_stage_class;

    class main_menu: public parent_stage
    {
    private:
    protected:
        void init_gui_objects() override
        {
            background = objects::gui::gui_object({{0, 0}, {1920, 0}, {1920, 1080}, {0, 1080}},{{960, 540}}, pre_loaded::background.get());
            elements.push_back(&background);

        }
        void init_event_objects() override;
        void init_game_objects() override
        {
        }
        void after_events() override
        {

        }

    public:
        objects::gui::gui_object background;
        main_menu(map<string, sh_p<info::parent>>& main_info):
                parent_stage(main_info){}
    };

}
