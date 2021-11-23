
#include "settings/library.h"
#include "settings/project_files.h"
using namespace sf;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    std::map<std::string, info::parent*> main_info;
//    main_info["render"] = new info::render(&window);
    objects::object<objects::gui_object>* a = new objects::gui_object(textures::banner_start_1.get(), Rect<float>(100, 100, 0.3, 0.3),
            new object_parameters::full_scale(), new object_parameters::common_draw());
    while (window.isOpen())
    {
        a->scale(window);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

        }
        window.clear();
        window.draw(*a);
        window.display();
    }
}