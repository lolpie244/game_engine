//
// Created by lolpie on 26.06.22.
//
#pragma once
#include <unordered_set>
#include <utility>
#include "sat_math.h"
#include "structs.h"
#include "../settings/constants_and_defines.h"


namespace helping_function
{
    using namespace std;
    using namespace structs;
    pair<double, double> get_max_segment(vector<Point>& figure, double k, double c)
    {
        double mx = constants::min_d;
        double mn = constants::max_d;
        for(int i = 0; i < figure.size(); i++)
        {
            auto projection_cords = point_projection(figure[i], k, c);
            double new_value = projection_cords.x + projection_cords.y;
            mx = max(mx, new_value);
            mn = min(mn, new_value);
        }
        return {mn, mx};
    }

    bool one_side_convex_collision(vector<Point>& first_figure, vector<Point>& second_figure)
    {
        unordered_set<double> set_of_k;
        size_t len = first_figure.size();
        for(int i = 0; i < len; i++)
        {
            auto equation = straight_line_equation(first_figure[i], first_figure[(i + 1) % len]);
            equation = get_perpendicular_line_equation(first_figure[i], equation.first, equation.second);
            double k = equation.first;
            double c = equation.second;
            if(set_of_k.count(k))
                continue;
            set_of_k.insert(k);
            if(!segments_collision(get_max_segment(first_figure, k, c), get_max_segment(second_figure, k, c)))
                return false;
        }
        return true;
    }
    bool collision(vector<vector<Point>>& first_figure, vector<vector<Point>>& second_figure)
    {
        for(auto first_convex_figure : first_figure)
            for(auto second_convex_figure: second_figure)
                if(one_side_convex_collision(first_convex_figure, second_convex_figure) &&
                    one_side_convex_collision(second_convex_figure, first_convex_figure))
                    return true;

        return false;
    }
    bool collision(vector<Point>& first_figure, vector<Point>& second_figure)
    {
        return one_side_convex_collision(first_figure, second_figure) &&
            one_side_convex_collision(second_figure, first_figure);
    }
}
