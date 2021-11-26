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
        gui->objects.emplace_back(new gui_object(textures::banner_start_1.get(), Rect<float>(200, 200, 0.2, 0.2),
                               new full_scale, new common_draw));
        auto window = info::get_info<info::render>(main_info, "render")->window;
        new event::button(gui->objects[0], print, print_1, gui->observer_list);
        new event::scale(gui->objects[0], window, gui->observer_list);

        main_info["gui"] = gui;

    }
}