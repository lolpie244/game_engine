
namespace info
{

    template <typename T, typename Map, typename Field>
    T* get_info(const Map& container, const Field& field)
    {
        return static_cast<T*>(container[field]);
    }
}