//
// Created by lolpie on 10/22/22.
//
namespace objects::parent
{
    using std::list;
    class composite_object: public abstract_object
    {
    public:
        composite_object()=default;
        virtual list<object*> get_objects(){}

        template<typename T>
        list<T*> get_objects()
        {
            list<T*> result;
            for(auto obj: get_objects())
            {
                auto casted = dynamic_cast<T*>(obj);
                if(casted)
                    result.push_back(casted);
            }
            return result;
        }
        virtual ~composite_object()=default;

    };
}