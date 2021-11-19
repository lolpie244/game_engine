
#include "settings/library.h"
#include "settings/project_files.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    std::map<std::string, info::parent*> main_info;
    main_info["render"] = new info::render(&window);


}