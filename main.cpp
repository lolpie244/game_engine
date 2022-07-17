#include "settings/library.h"
#include "settings/project_files.h"
using namespace sf;
using namespace std;
int main()
{
    auto figure_one = helping_function::concave_to_convexes({
        {2, 3}, {3, 5}, {5, 6}, {8, 5}, {7, 4}, {5, 5}, {4, 3}, {3, 2}, {3, 3}
                                                            });
    auto figure_two = helping_function::concave_to_convexes({
        {4, 4}, {5, 4}, {6, 3}, {6, 4}, {7, 3}, {6, 2}
    });
    cout << helping_function::collision(figure_one, figure_two);
//    sh_p<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!"));
//    window->setFramerateLimit(120);
//    std::map<std::string, sh_p<info::parent>> main_info;
//    main_info["render"] = shared_ptr<info::render>(new info::render(window));
//    auto events = &info::get_info<info::render>(main_info, "render")->event_manager;
//    events->bind_event(Event::Closed, [&window](Event event){window->close();});
//    events->bind_event(Event::Resized, [&window](Event event){
//        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
//        window->setView(sf::View(visibleArea));});
//    (new main_menu_np::main_menu(main_info))->main();
}