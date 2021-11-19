//
// Created by lolpie on 11/19/21.
//
namespace main_menu
{
    using namespace std;
    using namespace sf;
    void main(map<string, info::parent*> main_info)
    {
        shared_ptr<RenderWindow> window = info::get_info<info::render>(main_info, "render")->window;
        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();
                if(event.type == sf::Event::Resized)
                {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window->setView(sf::View(visibleArea));
                }

            }
            window->display();
        }
    }

}
