//
// Created by lolpie on 11/19/21.
//
namespace main_menu
{
    using namespace std;
    using namespace sf;
    void main(map<string, sh_p<info::parent>>& main_info)
    {
        format_gui(main_info);
        RenderWindow* window = info::get_info<info::render>(main_info, "render")->window.get();
        sh_p<info::render> render = info::get_info<info::render>(main_info, "render");
        sh_p<info::gui> gui = info::get_info<info::gui>(main_info, "gui");
        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
            {
                render->event_manager.notify(event);
                gui->event_manager.notify(event);
            }
            window->clear();
            gui->draw(*window);
            window->display();
        }
    }

}
