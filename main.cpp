#include "settings/library.h"
#include "settings/project_files.h"
using namespace sf;
using namespace std;
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sh_p<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings));
    window->setFramerateLimit(120);
    std::map<std::string, sh_p<info::parent>> main_info;
    main_info["render"] = shared_ptr<info::render>(new info::render(window));
    auto events = &info::get_info<info::render>(main_info, "render")->event_manager;
    events->bind_event(Event::Closed, [&window](Event event){window->close(); return false;});
    events->bind_event(Event::Resized, [&window](Event event){
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window->setView(sf::View(visibleArea)); return false;});
    (new main_menu_np::main_menu(main_info))->main();
}