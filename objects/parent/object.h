//
// Created by lolpie on 10/20/22.
//

namespace objects::parent
{
    using namespace structs;
    using sf::Texture, sf::Sprite;
    using std::vector, std::initializer_list, std::min, std::max, std::unordered_map;

    class object: public abstract_object
    {
    protected:
        Sprite sprite;
        sh_p<texture::common_texture> texture;
        structs::Point position;
        structs::Point size;
    public:

        object() = default;

        vector <structs::Point> points;

        sh_p<Texture> get_texture()
        {
            return this->texture->get_texture();
        }

        void update_texture(sh_p<texture::common_texture> new_texture, bool resize = true)
        {

            if(texture == nullptr)
            {
                texture = std::move(new_texture);
                if(size == Point({0, 0, 0}))
                    size = texture->get_texture()->getSize();
                this->sprite.setTexture(*texture->get_texture(), true);
                return;
            }

            Point old_texture_size = texture->get_texture()->getSize();
            texture = new_texture;
            Point new_texture_size = texture->get_texture()->getSize();

            this->sprite.setTexture(*texture->get_texture(), resize);

            if(resize)
                set_size(old_texture_size - new_texture_size + size);
        }
        void move(Point move_to)
        {
            set_position(position + move_to);
        }
        Sprite get_const_sprite() const
        {
            return this->sprite;
        }
        void set_size(Point new_size)
        {
            Point old_scale = size / get_texture()->getSize();
            Point new_scale = new_size / get_texture()->getSize();
            size = new_size;

            for(auto& point: points)
                point = (point / old_scale) * new_scale;
            Point sprite_scale = Point({sprite.getScale().x, sprite.getScale().y}) / old_scale * new_scale;

            sprite.setScale(sprite_scale.x , sprite_scale.y);
            Point sprite_origin = Point(texture->get_texture()->getSize()) / 2;
            this->sprite.setOrigin(sprite_origin.x, sprite_origin.y);
        }
        Sprite& get_sprite()
        {
            return this->sprite;
        }
        Point get_texture_scale()
        {
            return size / get_texture()->getSize();
        }
        Point get_position() const
        {
            return this->position;
        }
        Point get_left_corner() const
        {
            return position - size / 2;
        }
        void set_position(Point new_point)
        {
            position = new_point;
            this->sprite.setPosition(position.x, position.y);
            Point left_corner = get_left_corner();
            auto texture_points = texture->get_points();
            for(int i = 0; i < points.size(); i++)
                points[i] = texture_points[i] + left_corner;
        }
        void set_x_position(double x)
        {
            set_position({x, position.y, position.z});
        }
        Point get_size()
        {
            return size;
        }
        virtual ~object(){}
    };
    class object_constructor: virtual public object
    {
    public:
        object_constructor(){}

        object_constructor(Point position, Point size, sh_p<texture::common_texture> texture)
        {
            update_texture(std::move(texture));
            set_size(size);
            set_position(position);
        }
    };
}