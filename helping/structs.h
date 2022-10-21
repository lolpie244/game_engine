//
// Created by lolpie on 7/16/22.
//

namespace structs
{
    struct Point
    {
        double x;
        double y;
        double z;

        explicit Point(double x=0, double y=0, double z=0)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        template<typename T>
        Point(std::initializer_list<T> point_cords)
        {
            *this = point_cords;
        }
        Point operator+(Point other_cord) const
        {
            return Point(x + other_cord.x, y + other_cord.y, z + other_cord.z);
        }

        template<typename T1, typename T2>
        Point operator+(std::pair<T1, T2> other_cord) const
        {
            return Point(x + other_cord.first, y + other_cord.second, z);
        }

        Point operator*(Point other_cord) const
        {
            return Point(x * other_cord.x, y * other_cord.y, z + other_cord.z);
        }
        Point operator/(Point other_cord) const
        {
            return Point(
                    x / (other_cord.x != 0? other_cord.x: 1),
                    y / (other_cord.y != 0? other_cord.y: 1),
                    z / (other_cord.z != 0? other_cord.z: 1)
                        );
        }
        Point operator*(double k) const
        {
            return Point(x * k, y * k, z * k);
        }
        Point operator/(double k) const
        {
            return Point(x / k, y / k, z / k);
        }
        template<typename T1, typename T2>
        Point operator*(std::pair<T1, T2> other_cord) const
        {
            return Point(x * other_cord.first, y * other_cord.second);
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
            double* cords[3] = {&x, &y, &z};
            int k = 0;
            for(auto val : other_point)
                if(k == 3)
                    break;
                else
                    *cords[k++] = val;
            return *this;
        }
        friend std::ostream& operator<< (std::ostream &out, const Point &point);
    };
    std::ostream& operator<< (std::ostream &out, const Point &point)
    {
        out << "x = " << point.x << "; y = " << point.y << "; z = " << point.z;
        return out;
    }
}