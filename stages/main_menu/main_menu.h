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
            background = objects::gui::gui_object({960, 540}, {1920, 1080}, textures::background);

            start_button = objects::gui::button({960, 540, 1}, {200, 200}, textures::test_button);


            elements.insert({&start_button, &background});

        }
        void init_event_objects() override;
        void init_game_objects() override
        {
        }
        void after_events() override
        {

        }

    public:
        objects::gui::button start_button;
        objects::gui::gui_object background;
        vector<sh_p<objects::figures::figure_object>> points;
        main_menu(map<string, sh_p<info::parent>>& main_info):
                parent_stage(main_info){}
    };

}
