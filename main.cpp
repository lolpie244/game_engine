#define sh_p shared_ptr
#include "settings/library.h"
#include "settings/project_files.h"
using namespace sf;
using namespace std;
int main()
{
    sh_p<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!"));
    std::map<std::string, sh_p<info::parent>> main_info;
    sh_p<info::parent> test = sh_p<info::render>(new info::render(window));
//    main_info["render"]->print();
//    main_menu::main(main_info);
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            {
//                window.close();
//            }
//            if(event.type == sf::Event::Resized)
//            {
//                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
//                window.setView(sf::View(visibleArea));
//            }
//
//        }
//        window.clear();
//        window.display();
//    }
}