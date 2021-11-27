//
// Created by lolpie on 11/19/21.
//

namespace objects
{
    using namespace sf;
    using namespace std;
    class parent_object
    {
    protected:
        Sprite sprite;
        shared_ptr<Texture> texture;
    public:
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

        Vector2<float> left_corner_cords()
        {
            sf::Vector2<float> a(this->sprite.getGlobalBounds().left, this->sprite.getGlobalBounds().top);
            return a;
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
            this->texture = new_texture;
            this->sprite.setTexture(*texture, true);
            this->update_sprite();
        }
    };
}
