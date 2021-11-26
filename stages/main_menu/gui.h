//
// Created by lolpie on 11/25/21.
//

namespace main_menu
{
    using namespace std;
    using namespace sf;

    void print()
    {
        cout << "YES\n";
    }
    void format_gui(map<string, sh_p<info::parent>>& main_info)
    {
        sh_p<info::gui> gui(new info::gui());
        gui->objects.emplace_back(
                new objects::gui_object(textures::banner_start_1.get(), Rect<float>(200, 200, 0.2, 0.2),
                               new object_parameters::full_scale, new object_parameters::common_draw));
        auto pressButton = new event::press_button(gui->objects[0],
                                        sh_p<function<void(void)>>(new function<void(void)>([](){print();})));
        auto func = sh_p<function<void(sf::Event)>>(new function<void(sf::Event)>(
                [pressButton](sf::Event event){pressButton->press(event);}));
        gui->observer_list.get_observer(sf::Event::MouseButtonPressed).add_func(func);
        main_info["gui"] = gui;

    }
}