//
// Created by lolpie on 10/22/22.
//

namespace objects::parent
{
    class abstract_object
    {
    public:
        bool is_active = true;
        abstract_object()= default;
        virtual ~abstract_object()= default;
    };
}