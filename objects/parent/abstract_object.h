//
// Created by lolpie on 10/22/22.
//

namespace objects::parent
{
    int current_max_id = 0;
    class abstract_object
    {
        int id = current_max_id++;
    public:
        int get_id() const
        {
            return id;
        }
        bool is_active = true;
        virtual ~abstract_object()= default;

        bool operator<(const abstract_object& other) const
        {
            return id < other.get_id();
        }
        bool operator>(const abstract_object& other) const
        {
            return id > other.get_id();
        }
    };
}