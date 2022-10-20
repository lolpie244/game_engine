//
// Created by lolpie on 9/23/22.
//
namespace object_parameters
{
    using namespace sf;
    using namespace std;
    class static_move
    {
    public:
        virtual void move(Sprite& sprite, structs::Point speed){}
        virtual void move(Sprite& sprite, vector<structs::Point>& points, structs::Point speed){}
        virtual void move(vector<structs::Point>& points, vector<vector<structs::Point>>& convex_points, structs::Point speed){}
        virtual void move(Sprite& sprite, vector<structs::Point>& points, vector<vector<structs::Point>>& convex_points, structs::Point speed){}
    };
    class common_move: public static_move
    {
        void move(Sprite& sprite, vector<structs::Point>& points, vector<vector<structs::Point>>& convex_points, structs::Point speed) override
        {
            sprite.setPosition(sprite.getPosition().x + speed.x, sprite.getPosition().y + speed.y);
            move(points, convex_points, speed);
        }
        void move(vector<structs::Point>& points, vector<vector<structs::Point>>& convex_points, structs::Point speed) override
        {
            for(int i = 0; i < convex_points.size(); i++)
                for(structs::Point& point: convex_points[i])
                    point = point + speed;
            for(structs::Point& point: points)
                point = point + speed;
        }
    };
}