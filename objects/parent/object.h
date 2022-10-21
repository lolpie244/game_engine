//
// Created by lolpie on 10/20/22.
//

namespace parent
{
    using namespace structs;
    using sf::Texture, sf::Sprite;
    using std::vector, std::initializer_list, std::min, std::max, std::unordered_map;

    class object
    {
    protected:
        Sprite sprite;
        sh_p<Texture> texture;
        structs::Point position;
        structs::Point scale = {1, 1, 1};
        structs::Point left_up;
        structs::Point right_down;
    public:
        unordered_map<int, int> Events;
        bool is_active = true;
        object(){}

        object(initializer_list<Point> points, Point center, sh_p<Texture>& texture)
        {
            this->points = points;
            update_points();
            update_texture(texture);
            set_position(center);
            std::cout << sprite.getPosition().x << ' ' << sprite.getPosition().y << '\n';
        }

        vector <structs::Point> points;


        sh_p<Texture> get_texture()
        {
            return this->texture;
        }
        void update_sprite()
        {
            if(points.empty())
                return;
            auto texture_size = texture->getSize();
            Point sprite_scale = {(right_down.x - left_up.x) / texture_size.x * scale.x,
                                 (right_down.y - left_up.y) / texture_size.y * scale.y};

            sprite.setScale(sprite_scale.x, sprite_scale.y);

            sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

        }

        void update_texture(sh_p <Texture> &new_texture)
        {
            this->texture = new_texture;
            this->sprite.setTexture(*texture);
            update_sprite();
        }

        Sprite get_const_sprite() const
        {
            return this->sprite;
        }
        void update_points()
        {
            if(points.empty())
                return;
            left_up = points[0];
            right_down = points[0];
            for(const auto& point: points)
            {
                left_up = {min(left_up.x, point.x), min(left_up.y, point.y)};
                right_down = {max(right_down.x, point.x), max(right_down.y, point.y)};
            }
        }
        Sprite& get_sprite()
        {
            return this->sprite;
        }

        Point get_position() const
        {
            return this->position;
        }
        void set_position(Point new_point)
        {
            position = new_point;
            this->sprite.setPosition(position.x, position.y);
        }
        Point get_scale()
        {
            return scale;
        }
        Point rect_size()
        {
            return right_down - left_up;
        }
        virtual ~object() {}
    };

}