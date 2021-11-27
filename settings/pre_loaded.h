//
// Created by lolpie on 14.11.21.
//

namespace pre_loaded
{
    using namespace std;
    using namespace sf;
    template<typename Type>
    class loaded_info
    {
        shared_ptr<Type> texture_;
        string path;
    public:
        loaded_info(const string& path)
        {
            this->path = path;
        }
        shared_ptr<Type>& get()
        {
            if(texture_ == nullptr)
            {
                texture_ = shared_ptr<Type>(new Type);
                texture_->loadFromFile(path);
            }
            return texture_;
        }
    };
    loaded_info<Texture> banner_start_1("textures/game/banner_start_1.png");
    loaded_info<Texture> background("textures/gui/background.png");
    loaded_info<Texture> pixel("textures/gui/pixel.png");
    loaded_info<Texture> red_button("textures/gui/red_button.png");
    loaded_info<Texture> red_button_pressed("textures/gui/red_button_pressed.png");
    loaded_info<Texture> play("textures/gui/play.png");
    loaded_info<Texture> play_pressed("textures/gui/play_pressed.png");
    loaded_info<Texture> back("textures/gui/back.png");
    loaded_info<Texture> back_pressed("textures/gui/back_pressed.png");

    loaded_info<Font> button_font("textures/fonts/button.ttf");


}
