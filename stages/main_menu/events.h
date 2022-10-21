//
// Created by lolpie on 11/25/21.
//



namespace main_menu_np
{
    using namespace std;
    using namespace sf;
    using helping_function::Point, helping_function::get_scaled_mouse_position, helping_function::get_mouse_position;

    bool construct_convex_press(sf::Event event, main_menu* screen_stage)
    {
        Point mouse = get_scaled_mouse_position(*screen_stage->window);
        auto point = new objects::figures::figure_object({{0, 0}, {10, 0}, {10, 100}, {0, 10}}, {mouse.x, mouse.y, 1.0}, pre_loaded::dot.get());
        point->set_scale(new objects::mixins::full_scale_2d);
        screen_stage->elements.push_back(point);
        return true;
    }

    void main_menu::init_event_objects()
    {
        elements.event_manager.bind_event(sf::Event::MouseButtonPressed,
        [this](sf::Event event){return construct_convex_press(event, this);}, &background);
    }

}
