//
// Created by lolpie on 10/20/22.
//
#pragma once
#include "../parent/composite_object.h"
#include "../../helping/structs.h"
#include "../mixins/includes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <array>
#include <vector>
#include "../parent/composite_object.h"


namespace objects{ namespace figures
{
	using structs::Point, std::vector;
	using mixins::CompositeDrawable, mixins::CompositeScalable;
	using sf::RenderTarget, sf::RenderStates;
	using parent::composite_object;

    class bezier: virtual public parent::composite_object, public CompositeDrawable, public CompositeScalable
    {
		vector<Point> points;
    public:
		void add_point(Point point)
		{
			points.push_back(point);
			if(points.size() == 5)
				points.erase(points.begin());
		}
		vector<Point*> get_points() const override
		{
			vector<Point*> result;
			for(const Point& point: points)
				result.push_back(const_cast<Point*>(&point));
			return result;
		}
    };
	class BezierDraw: public objects::mixins::CompositeCommonDraw
	{
	public:
		void draw(RenderTarget &target, RenderStates states, const composite_object* composite_obj) override
		{
			auto points = composite_obj->get_points();
			for(int i = 0; i < points.size() - 1; i++)
			{
				sf::CircleShape circle(20);
				circle.setPosition(*points[i]);
				sf::Vertex line[] =
				{
					sf::Vertex(*points[i]),
					sf::Vertex(*points[i + 1])
				};
				target.draw(circle);
				target.draw(line, 2, sf::Lines);
			}
		}
	};
}}

