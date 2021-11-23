//
// Created by lolpie on 11/23/21.
//

namespace helping_classes
{
    template<typename T>
    class Type
    {
    public:
        T* cast(void* obj)
        {
            return static_cast<T*>(obj);
        }
    };

}