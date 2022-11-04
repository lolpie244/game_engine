//
// Created by lolpie on 10/20/22.
//
#pragma once
#include "../parent/composite_object.h"
#include "../../helping/structs.h"
#include "../../helping/function_with_delay.h"
#include "../../helping/helping_math.h"
#include "../../settings/constants_and_defines.h"
#include "../mixins/includes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <vector>
#include "../parent/composite_object.h"
#include "line.h"
#include <cmath>

namespace objects{ namespace figures
{
	using structs::Point, std::vector;
	using mixins::CompositeDrawable, mixins::CompositeScalable;
	using sf::RenderTarget, sf::RenderStates;
	using parent::composite_object, parent::object;
	using helping_function::lerp;

    class Bezier;
	class BezierDraw;

	enum BezierDisplay
	{
		only_curve, with_points, with_helping_lines

	};
	class BezierPoint: public mixins::DraggableMove, public mixins::Drawable
	{
		sf::CircleShape circle;
    protected:
        Point* get_position_pointer()
        {
            return &position;
        }
		vector<Bezier*> linked_beziers;
	public:
		void set_size(double radius)
		{
			circle.setRadius(radius);
			this->size = {radius * 2, radius * 2};
		}
		void set_position(Point position) override
		{
			this->position = position;
			circle.setPosition(position - (size / 2));
		}
		void set_color(sf::Color new_color)
		{
			circle.setFillColor(new_color);
		}
		BezierPoint()
		{
			mixins::Clickable::with_check_transparency = false;
			with_check_transparency = false;
		}
		BezierPoint(Point position, double radius, sf::Color color = sf::Color::Red)
		{
			set_size(radius);
			set_position(position);
			circle.setFillColor(color);
			BezierPoint();
		}
		virtual void draw(RenderTarget& target, RenderStates states) const override
		{
			if(is_to_display())
				target.draw(circle);
		}
		operator Point()
		{
			return this->position;
		}

        friend class Bezier;
	};
    class Bezier: virtual public parent::composite_object, public CompositeDrawable, public CompositeScalable
    {
		double point_size()
		{
			return tickness * 2;
		}
		Curve curve;
		vector<Line> helping_lines;
		vector<BezierPoint> helping_points;

		void update_curve()
		{
			if(points.size() <= 2)
				return;
			vector<BezierPoint> initial_points;
			for(auto point: points)
				initial_points.push_back(*point);
			curve = Curve(tickness, color);
			helping_lines.clear();
			helping_points.clear();

			for(double t = 0; t <= this->max_t + step; t += step)
			{
				vector<BezierPoint> points = initial_points;
				while(points.size() > 1)
				{
					vector<BezierPoint> temp;
					for(int i = 0; i + 1 < points.size(); i++)
					{
						Point a = points[i];
						Point b = points[i + 1];
						auto new_point = BezierPoint({lerp(a.x, b.x, t), lerp(a.y, b.y, t)}, point_size());
						temp.push_back(new_point);
						if(t < max_t)
							continue;
						helping_lines.push_back(Line(a, b, 2, sf::Color::Red));
						helping_points.push_back(new_point);
					}
					points = std::move(temp);
				}
				curve.push_back(points[0]);
			}
			helping_points[helping_points.size() - 1].set_color(sf::Color::Blue);
		}
		void bind_update_curve(sh_p<BezierPoint> point, events::observer_list& observer)
		{
			point->bind_drag([point](sf::Event event){
					for(auto bezier: point->linked_beziers)
						bezier->update_curve_with_delay();
					return true;
				}, observer);
		}
		BezierDisplay display_type;
		double max_t = 1;

	public:
		helping_function::FuncWithDelay<std::function<void()>> update_curve_with_delay;
		vector<sh_p<BezierPoint>> points;
		double step = 0.01;
		double tickness = 6;
		sf::Color color = sf::Color::Black;
		Bezier():
			update_curve_with_delay(helping_function::FuncWithDelay<std::function<void()>>([this](){ this->update_curve();}, 30))
		{
		}
		Bezier(Point position, BezierDisplay display_type = only_curve, double tickness = 6, sf::Color color = sf::Color::Black):
			update_curve_with_delay(helping_function::FuncWithDelay<std::function<void()>>([this](){ this->update_curve();}, 30))
		{
			this->position = position;
			this->tickness = tickness;
			this->color = color;
			set_diaplay_type(display_type);
		}
		BezierDisplay get_display_type()
		{
			return display_type;
		}
		void clear()
		{
			points.clear();
			helping_points.clear();
			helping_lines.clear();
			curve.clear();
		}
		void set_diaplay_type(BezierDisplay display_type)
		{
			this->display_type = display_type;
			for(auto i : points)
				i->is_active = display_type != only_curve;
		}
		int points_count()
		{
			return this->points.size();
		}
		void push_back(Point point, mixins::observer_list& observer)
		{
			push_back(point);
			bind_update_curve(last_point(), observer);
		}
		void push_back(Point point)
		{
			points.push_back(std::make_shared<BezierPoint>(point, point_size()));
			if(display_type == only_curve)
				last_point()->is_active = false;
			last_point()->linked_beziers.push_back(this);
			update_curve();
		}
		void push_back(sh_p<BezierPoint> point)
		{
			points.push_back(point);
			last_point()->linked_beziers.push_back(this);
			update_curve();
		}
		void pop_back()
		{
			points.pop_back();
			update_curve();
		}
		void erase(int position)
		{
			points.erase(points.begin() + position);
			update_curve();
		}
		void insert(Point point, int position, mixins::observer_list& observer)
		{
			insert(point, position);
			bind_update_curve(points[position], observer);
		}
		void insert(Point point, int position)
		{
			points.insert(points.begin() + position, std::make_shared<BezierPoint>(point, point_size()));
			if(display_type == with_points)
				points[position]->is_active = false;
			points[position]->linked_beziers.push_back(this);
			update_curve();
		}
		sh_p<BezierPoint> last_point()
		{
			return points[points.size() - 1];
		}
		void set_max_t(double value)
		{
			max_t = value;
			update_curve_with_delay();
		}
		friend BezierDraw;
    };

	class BezierDraw: public objects::mixins::CompositeCommonDraw
	{
	public:
		void draw(RenderTarget &target, RenderStates states, const composite_object* composite_obj) override
		{
			auto bezier = dynamic_cast<Bezier*>(const_cast<composite_object*>(composite_obj));
			target.draw(bezier->curve);
			if(bezier->display_type == only_curve)
				return;
			if(bezier->display_type == with_points)
			{
				Curve line_to_draw(2, sf::Color::Green);

				for(auto point: bezier->points)
				{
					target.draw(*point);
					if(point->is_to_display())
						line_to_draw.push_back(*point);
				}
				target.draw(line_to_draw);
			}
			if(bezier->display_type == with_helping_lines)
			{
				for(auto i: bezier->helping_lines)
					target.draw(i);
				for(auto i: bezier->helping_points)
					target.draw(i);
			}
		}
	};
}}

