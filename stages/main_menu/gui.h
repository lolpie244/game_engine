//
// Created by lolpie on 11/25/21.
//

namespace main_menu
{
    using namespace std;
    using namespace sf;
    using namespace object_parameters;
    using namespace objects;
    void print()
    {
        cout << "S\n";
    }
    void print_1()
    {
        cout << "YE\n";
    }
    void format_gui(map<string, sh_p<info::parent>>& main_info)
    {
        sh_p<info::gui> gui(new info::gui());
        auto window = info::get_info<info::render>(main_info, "render")->window;

        gui->objects.emplace_back(new gui_object(textures::test.get(), Rect<float>(960, 540, 1, 1),
                                  new coord_scale, new common_draw));
        new event::scale(gui->objects[gui->objects.size() - 1], window, gui->event_manager);

        gui->objects.emplace_back(new gui_object(textures::banner_start_1.get(), Rect<float>(200, 200, 0.2, 0.2),
                               new full_scale, new common_draw));

        new event::button(gui->objects[gui->objects.size() - 1], print, print_1, gui->event_manager);
        new event::scale(gui->objects[gui->objects.size() - 1], window, gui->event_manager);

        main_info["gui"] = gui;

    }
}