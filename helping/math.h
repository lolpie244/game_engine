//
// Created by lolpie on 26.06.22.
//

namespace helping_function
{
    using namespace std;
    using namespace constants;
    pair<double, double> straight_line_equation(pair<double, double> first_point, pair<double, double> second_point)
    {
        if(first_point.first == second_point.first)
            return {inf, inf};
        double k = (first_point.second - second_point.second) / (first_point.first - second_point.first);
        double c = first_point.second - k * first_point.first;
        return {k, c};
    }
    pair<double, double> get_perpendicular_line_equation(pair<double, double> point, double k, double c)
    {
        k = -1 * (1 / k);
        c = point.second - k * point.first;
        return {k, c};
    }
    pair<double, double> point_projection(pair<double, double> point, double k, double c)
    {
        if(k == inf)
            return {0, point.second};
        double x = (k * (point.second - c) + point.first) / (k * k + 1);
        double y = k * x + c;
        return {x, y};
    }

    bool segments_collision(pair<double, double> first_segment, pair<double, double> second_segment)
    {
        if(first_segment.second < first_segment.first)
            swap(first_segment.first, first_segment.second);
        if(second_segment.second < second_segment.first)
            swap(second_segment.first, second_segment.second);

        double points[] = {first_segment.first, first_segment.second, second_segment.first, second_segment.second};
        for(int i = 0; i < 4; i++)
        {
            int j = (i - (i % 2 != 0) + 2) % 4;
            if(points[j] <= points[i] && points[i] <= points[j + 1])
                return true;
        }
        return false;
    }
}