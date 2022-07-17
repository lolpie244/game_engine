//
// Created by lolpie on 7/16/22.
//

namespace structs
{
    struct Point
    {
        double x{};
        double y{};

        explicit Point(double x=0, double y=0)
        {
            this->x = x;
            this->y = y;
        }

        template<typename T>
        Point(std::initializer_list<T> point_cords)
        {
            *this = point_cords;
        }
        Point operator+(Point other_cord) const
        {
            return Point(x + other_cord.x, y + other_cord.y);
        }

        template<typename T_1, typename T_2>
        Point& operator=(std::pair<T_1, T_2> other_point)
        {
            this->x = other_point.first;
            this->y = other_point.second;
            return *this;
        }

        template<typename T>
        Point& operator=(std::initializer_list<T> other_point)
        {
            bool flag = false;
            for(auto val : other_point)
                if(!flag)
                {
                    this->x = val;
                    flag = true;
                }
                else
                {
                    this->y = val;
                    break;
                }
            return *this;
        }
        friend std::ostream& operator<< (std::ostream &out, const Point &point);
    };
    std::ostream& operator<< (std::ostream &out, const Point &point)
    {
        out << "x = " << point.x << "; y = " << point.y;
        return out;
    }
}