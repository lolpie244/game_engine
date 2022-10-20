//
// Created by lolpie on 11/19/21.
//



namespace object_parameters
{
    using namespace sf;
    class common_draw
    {
    public:
        virtual void draw(RenderTarget& target, RenderStates states, const Sprite& sprite, Texture& texture) const
        {
            target.draw(sprite, states);
        }
        virtual void draw(RenderTarget& target, RenderStates states, const std::vector<structs::Point>& points, Color color = Color::Green) const
        {
            if(points.size() == 1)
            {
                auto vertex = sf::Vertex(Vector2f(points[0].x, points[0].y), color);
                target.draw(&vertex, 1, sf::Points);
                return;
            }
            if(points.size() == 2)
            {
                sf::VertexArray vertexes(sf::LinesStrip, 2);
                int i = 0;
                for(auto point: points)
                    vertexes[i++] = sf::Vertex(Vector2f(point.x, point.y), color);
                target.draw(vertexes);
                return;
            }
            sf::ConvexShape convex;
            convex.setPointCount(points.size());

            convex.setFillColor(color);
            int i = 0;
            for(auto point : points)
                convex.setPoint(i++, Vector2f(point.x, point.y));
            target.draw(convex);
        }
        virtual void draw(RenderTarget& target, RenderStates states, Text& text) const
        {
            target.draw(text);
        }
    };
}