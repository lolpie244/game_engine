#include <utility>

//
// Created by lolpie on 11/19/21.
//
namespace main_menu_np
{
    using namespace std;
    using namespace sf;
    using namespace parent_stage_class;

    using helping_function::Point;

    class test_figure: public objects::gui::gui_object, public objects::mixins::Draggable
    {
    public:
        test_figure() =default;
        test_figure(helping_function::Point position, Point size, sh_p<texture::common_texture> new_texture):
            objects::gui::gui_object(position, size, std::move(new_texture)){}
    };
    class main_menu: public parent_stage
    {
    private:
    protected:
        void init_gui_objects() override
        {
            background = objects::gui::gui_object({960, 540}, {1920, 1080}, textures::background);

            start_button = objects::gui::button({960, 540, 1}, {200, 200}, textures::test_button);
            drag_test = test_figure({700, 540, 1}, {200, 200}, textures::test_button->get_released());

            slider = objects::gui::Slider({350, 300, 2}, {688, 78}, textures::test_slider);

            elements.insert(slider.get_objects());
            elements.insert({&start_button, &background, &drag_test});
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
        test_figure drag_test;
        objects::gui::Slider slider;
        vector<sh_p<objects::figures::figure_object>> points;
        main_menu(map<string, sh_p<info::parent>>& main_info):
                parent_stage(main_info){}
    };

}
