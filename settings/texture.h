#include <memory>
#include <utility>

//
// Created by lolpie on 14.11.21.
//

namespace texture
{
    using namespace std;
    using namespace sf;
    using helping_function::Point;
    class common_texture
    {
    protected:
        shared_ptr<Texture> texture;
        vector<Point> points;
        string path;

        virtual void load_texture()
        {
            if(texture == nullptr)
            {
                texture = std::make_shared<Texture>();
                texture->loadFromFile(path);
            }
        }
    public:
        common_texture()= default;
        explicit common_texture(const string &path, vector<Point> new_points={})
        {
            this->path = path;
            this->points = std::move(new_points);
        }

        shared_ptr<Texture>& get_texture()
        {
            load_texture();
            return texture;
        }
        vector<Point> get_points()
        {
            if(points.empty())
            {
                load_texture();
                Point size = texture->getSize();
                points = {{0.0, 0.0}, {size.x, 0.0}, {size.x, size.y}, {0.0, size.y}};
            }
            return points;
        }
    };
    class button
    {
    protected:
        sh_p<common_texture> pressed_texture;
        sh_p<common_texture> released_texture;
    public:
        button()=default;
        button(const string &released_path, const string& pressed_path)
        {
            this->pressed_texture = make_shared<common_texture>(pressed_path);
            this->released_texture = make_shared<common_texture>(released_path);
        }
        sh_p<common_texture> get_pressed()
        {
            return pressed_texture;
        }
        sh_p<common_texture> get_released()
        {
            return released_texture;
        }
    };

    class slider
    {
        sh_p<common_texture> slider_texture;
        sh_p<common_texture> picker_texture;
        pair<Point, Point> picker_segment_points;
    public:
        slider(const string &slider_path, const string& picker_path, Point start_point, Point end_point)
        {
            this->slider_texture = make_shared<common_texture>(slider_path);
            this->picker_texture = make_shared<common_texture>(picker_path);
            this->picker_segment_points = {start_point, end_point};
        }
        pair<Point, Point> get_picker_segment()
        {
            return picker_segment_points;
        }
        sh_p<common_texture> get_slider()
        {
            return slider_texture;
        }
        sh_p<common_texture> get_picker()
        {
            return picker_texture;
        }
    };
    common_texture pixel("textures/pixel.png");


}
