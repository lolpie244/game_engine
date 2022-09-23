//
// Created by lolpie on 26.06.22.
//

namespace helping_function
{
    using namespace std;
    using namespace constants;
    using namespace structs;


    pair<double, double> straight_line_equation(Point first_point, Point second_point)
    {
        if(first_point.x == second_point.x)
            return {inf, inf};
        double k = (first_point.y - second_point.y) / (first_point.x - second_point.x);
        double c = first_point.y - k * first_point.x;
        return {k, c};
    }
    pair<double, double> get_perpendicular_line_equation(Point point, double k, double c)
    {
        k = -1 * (1 / k);
        c = point.y - k * point.x;
        return {k, c};
    }
    Point point_projection(Point point, double k, double c)
    {
        if(k == inf)
            return Point(0, point.y);
        double x = (k * (point.y - c) + point.x) / (k * k + 1);
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
    double signed_triangle_area (Point p1, Point p2, Point p3)
    {
        return ((p2.x - p1.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - p1.y)) / 2.0;
    }

    vector<vector<Point>> concave_to_convexes(vector<Point>& figure)
    {
        int size = figure.size();
        bool start_direction = signed_triangle_area(figure[size - 1], figure[0], figure[1]) <= 0;
        for(int i = 0; i < size; i++)
        {
            bool direction = signed_triangle_area(figure[(i - 1 + size) % size], figure[i], figure[(i + 1) % size]) <= 0;
            if(direction == start_direction)
                continue;
            int j = i + 1;
            while(signed_triangle_area(figure[(i - 1 + size) % size], figure[i], figure[j]) > 0)
                j = (j + 1) % size;


            if(i < j)
                swap(i, j);
            vector<Point> sub_figure_1, sub_figure_2;
            for(int k = j; k <= i; k++)
                sub_figure_1.push_back(figure[k]);

            for(int k = i; k != j; k = (k + 1) % size)
                sub_figure_2.push_back(figure[k]);

            sub_figure_2.push_back(figure[j]);

            auto ans = concave_to_convexes(sub_figure_1);
            auto to_ans = concave_to_convexes(sub_figure_2);

            move(to_ans.begin(), to_ans.end(), back_inserter(ans));
            return ans;
        }
        return {figure};
    }
}