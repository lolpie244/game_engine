#define sh_p shared_ptr
#include "settings/library.h"
#include "settings/project_files.h"
using namespace sf;
using namespace std;
int main()
{
    sh_p<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!"));
    std::map<std::string, sh_p<info::parent>> main_info;
    main_info["render"] = shared_ptr<info::render>(new info::render(window));
    main_menu::main(main_info);
}