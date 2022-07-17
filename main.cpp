#include "settings/library.h"
#include "settings/project_files.h"
using namespace sf;
using namespace std;
int main()
{
//    cout << helping_function::signed_triangle_area({4, 2}, {5, 4}, {6, 1}) << '\n';
//    cout << helping_function::signed_triangle_area({5, 4}, {6, 1}, {1, 0}) << '\n';
//    vector<structs::Point> main_figure = {{1, 4}, {3, 9}, {9, 8}, {6, 7}, {5, 6}, {4, 4}, {6, 1}, {3, 2}, {1, 1}};
    vector<structs::Point> main_figure =
            {{0, 4}, {1, 8}, {5, 6}, {4, 9}, {10, 8}, {13, 6}, {4, 5}, {13, 4}, {7, 3}, {8, 1}, {6, 0}, {2, 4}, {4, 1}, {3, 1}};
    auto ans = helping_function::concave_to_convexes(main_figure);
    cout << "LEN: " << ans.size() << '\n';
    for(auto figure: ans)
    {
        for(auto point: figure)
            cout << point << '\n';
        cout << "--------------------------------\n";
    }

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