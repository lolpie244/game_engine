#include "settings/constants_and_defines.h"
#include "settings/project_files.h"
// #include "stages/draw_bezier/draw_bezier_stage.h"
#include "stages/draw_bezier/events.h"
#include "stages/detail_bezier/events.h"
using namespace sf;
using namespace std;
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sh_p<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings));
	constants::current_window = window;
    window->setFramerateLimit(60);
    std::map<std::string, sh_p<info::parent>> main_info;
    main_info["render"] = shared_ptr<info::render>(new info::render(window));
    auto events = &info::get_info<info::render>(main_info, "render")->event_manager;
    events->bind(Event::Closed, [&window](Event event) {
        window->close();
        return false;
    });
    events->bind(Event::Resized, [&window](Event event) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window->setView(sf::View(visibleArea));
        return false;
    });
    // (new draw_bezier_np::draw_bezier(main_info))->main();
    (new detail_bezier_np::detail_bezier(main_info))->main();
}
