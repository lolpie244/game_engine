//
// Created by lolpie on 10/22/22.
//

namespace objects::parent
{
    class abstract_object
    {
        static int current_max_id;
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
    int abstract_object::current_max_id = 0;
}