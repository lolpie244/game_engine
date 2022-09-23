//
// Created by lolpie on 11/19/21.
//

namespace objects_np
{
    using namespace sf;
    using namespace std;
    class parent_object: public Drawable
    {
    protected:
        Sprite sprite;
        shared_ptr<Texture> texture;
        bool with_texture = false;
        int depth = 0;
    public:
        vector<structs::Point> points;
        vector<vector<structs::Point>> convex_points;
        bool is_active = true;
        void update_sprite()
        {
            auto size = this->get_local_size();
            this->sprite.setOrigin(size.x / 2.0, size.y / 2.0);
        }

        shared_ptr<Texture> get_texture()
        {
            return this->texture;
        }

        Sprite& get_sprite()
        {
            return this->sprite;
        }
        void concave_to_convex()
        {
            if(this->points.empty())
                convex_points = {get_rect()};
            else
                convex_points = helping_function::concave_to_convexes(points);
        }
        bool has_texture()
        {
            return with_texture;
        }
        Vector2<float> left_corner_cords()
        {
            sf::Vector2<float> a(this->sprite.getGlobalBounds().left, this->sprite.getGlobalBounds().top);
            return a;
        }
        vector<structs::Point> get_rect()
        {
            auto pos = this->get_position();
            auto size = this->get_size();
            return {
                {pos.x, pos.y},
                {pos.x + size.x, pos.y},
                {pos.x + size.x, pos.y + size.y},
                {pos.x, pos.y + size.y},
            };
        }
        Vector2<float> get_position()
        {
            return this->sprite.getPosition();
        }

        Vector2<float> get_size()
        {
            sf::Vector2<float> a(this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height);
            return a;
        }
        Vector2<float> get_local_size()
        {
            sf::Vector2<float> a(this->sprite.getLocalBounds().width, this->sprite.getLocalBounds().height);
            return a;
        }
        Vector2<float> get_scale()
        {
            return this->sprite.getScale();
        }
        void update_texture(sh_p<Texture>& new_texture)
        {
            this->with_texture = true;
            this->texture = new_texture;
            this->sprite.setTexture(*texture, true);
            this->update_sprite();
        }

    };
}
