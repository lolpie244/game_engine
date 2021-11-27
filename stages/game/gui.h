//
// Created by lolpie on 11/25/21.
//



namespace game
{
    using namespace std;
    using namespace sf;
    using namespace object_parameters;
    using namespace objects;
    void format_gui(map<string, sh_p<info::parent>>& main_info)
    {
        sh_p<info::gui> gui(new info::gui());
        gui->objects.emplace_back(new gui_objects(pre_loaded::background.get(), Rect<float>(960, 540, 0.5, 0.5),
                                                  new coord_scale, new common_draw));


        gui->objects.emplace_back(new button(pre_loaded::back.get(), pre_loaded::back_pressed.get(),
                     Rect<float>(500, 500, 2, 2),new full_scale, new common_draw));
        new event::button(gui->objects[gui->objects.size() - 1], [](){}, [&main_info](){ back_press(main_info);}, gui->event_manager);


        auto window = info::get_info<info::render>(main_info, "render")->window;
        for(auto i : gui->objects)
        {
            i->scale(*window);
            new event::scale(i, window, gui->event_manager);
        }
        main_info["gui"] = gui;

    }
}