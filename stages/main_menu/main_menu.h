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
        sh_p<info::gui> gui = info::get_info<info::gui>(main_info, "gui");
        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    cout << event.type << ' ' << sf::Event::EventType::MouseButtonPressed << '\n';
                    window->close();
                }
//                if(typeid(event).name() == typeid(sf::Event::MouseButtonPressed).name())

                gui->observer_list.get_observer(event).notify(event);
//                if(event.type == sf::Event::Resized)
//                {
//                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
//                    window->setView(sf::View(visibleArea));
//                }

            }
            window->clear();
            gui->draw(*window);
            window->display();
        }
    }

}
