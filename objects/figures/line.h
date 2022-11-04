
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../../helping/structs.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>
#include <iterator>
#include <vector>
namespace objects{ namespace figures
{
	using structs::Point, std::sqrt;

	class Line : public sf::Drawable
	{
		sf::Vertex vertices[4];
		double thickness;
		sf::Color color;
		public:
			Line(const Point& point1, const Point& point2, double thickness = 5, sf::Color color = sf::Color::Black)
			{
				this->color = color;
				this->thickness = thickness;
				Point direction = point2 - point1;
				Point unitDirection = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
				Point unitPerpendicular(-unitDirection.y, unitDirection.x);

				Point offset = unitPerpendicular * (thickness / 2.0);

				vertices[0].position = point1 + offset;
				vertices[1].position = point2 + offset;
				vertices[2].position = point2 - offset;
				vertices[3].position = point1 - offset;

				for (int i = 0; i < 4; i++)
					vertices[i].color = color;
			}

			void draw(sf::RenderTarget &target, sf::RenderStates states) const
			{
				target.draw(vertices, 4, sf::Quads);
			}
			template<typename T1, typename T2>
			static void draw_lines(std::iterator<T1, T2> first, std::iterator<T1, T2> last, sf::RenderTarget& window)
			{
				for(auto& i = first; i != last; i++)
					window.draw(*i);
			}
	};
	class Curve: public sf::Drawable, public std::vector<Point>
	{
	public:
		int thickness = 5;
		sf::Color color = sf::Color::Black;

		Curve(int thickness = 5, sf::Color color = sf::Color::Black)
		{
			this->thickness = thickness;
			this->color = color;
		}
		void draw(sf::RenderTarget &target, sf::RenderStates states) const
		{
			for(int i = 0; i + 1 < this->size(); i++)
				target.draw(Line((*this)[i], (*this)[i + 1], this->thickness, this->color));
		}
	};
}}
