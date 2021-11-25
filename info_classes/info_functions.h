
namespace info
{
    using namespace std;
    template <typename T, typename Map, typename Field>
    sh_p<T> get_info(Map& container, const Field& field)
    {
        return static_pointer_cast<T>(container[field]);
    }
}