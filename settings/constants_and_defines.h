//
// Created by lolpie on 26.06.22.
//

#define sh_p std::shared_ptr

using event_function_type = std::function<bool(sf::Event)>;
namespace constants
{
    double inf = std::numeric_limits<double>::infinity();
    double min_d = std::numeric_limits<double>::min();
    double max_d = std::numeric_limits<double>::max();
}