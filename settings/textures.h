//
// Created by lolpie on 14.11.21.
//

namespace textures
{
    using namespace std;
    using namespace sf;
    class loaded_texture
    {
        shared_ptr<Texture> texture_;
        string path;
    public:
        loaded_texture(const string& path)
        {
            this->path = path;
        }
        shared_ptr<Texture>& get()
        {
            if(texture_ == nullptr)
            {
                texture_ = shared_ptr<Texture>(new Texture);
                texture_->loadFromFile(path);
            }
            return texture_;
        }
    };
    loaded_texture banner_start_1("textures/banner_start_1.png");
    loaded_texture test("textures/test.png");
    loaded_texture pixel("textures/pixel.png");

}
