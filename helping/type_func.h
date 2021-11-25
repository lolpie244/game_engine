//
// Created by lolpie on 11/23/21.
//

namespace helping_function
{
    using namespace std;
    template<typename T>
    sh_p<T> to_share(T* val)
    {
        return sh_p<T>(val);
    }
    template<typename T>
    sh_p<T> to_share(T& val)
    {
        return sh_p<T>(&val);
    }

}