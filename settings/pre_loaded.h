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
    loaded_info<Texture> background("textures/background.jpg");
    loaded_info<Texture> dot("textures/dot.png");
    loaded_info<Texture> pixel("textures/pixel.png");

    loaded_info<Texture> blue_plus_pressed("textures/blue_plus_pressed.png");
    loaded_info<Texture> blue_plus_released("textures/blue_plus_released.png");
    loaded_info<Texture> blue_ok_pressed("textures/blue_ok_pressed.png");
    loaded_info<Texture> blue_ok_released("textures/blue_ok_released.png");
    loaded_info<Texture> green_plus_released("textures/green_plus_released.png");
    loaded_info<Texture> green_plus_pressed("textures/green_plus_pressed.png");
    loaded_info<Texture> green_ok_pressed("textures/green_ok_pressed.png");
    loaded_info<Texture> green_ok_released("textures/green_ok_released.png");


}
