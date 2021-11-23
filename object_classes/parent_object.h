//
// Created by lolpie on 11/19/21.
//

namespace objects
{
    using namespace sf;
    using namespace std;
    template<typename Type = int>
    class parent_object
    {
    protected:
        Sprite sprite;
        shared_ptr<Texture> texture;
        helping_classes::Type<Type> type;
    public:
        Type* cast()
        {
            return type.cast(this);
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
        Vector2<float> get_scale()
        {
            return this->sprite.getScale();
        }
    };
}
