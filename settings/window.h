//
// Created by lolpie on 14.11.21.
//

namespace settings
{
    using namespace std;
    using namespace sf;
    Vector2<float> get_window_scale(Window& window)
    {
        auto size = window.getSize();
        return Vector2<float>(size.x / 1920.0, size.y / 1080.0);
    }

}

