//
// Created by lolpie on 11/23/21.
//

namespace helping_function
{
    using namespace std;

    sf::Vector2<float> get_window_scale(sf::Window &window)
    {
        auto size = window.getSize();
        return sf::Vector2<float>(size.x / 1920.0, size.y / 1080.0);
    }
}