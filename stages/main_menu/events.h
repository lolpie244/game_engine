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
        sh_p<objects::figures::figure_object> point(
                new objects::figures::figure_object({mouse.x, mouse.y, 1.1}, {100, 100}, textures::dot));

        screen_stage->points.push_back(point);

        point->set_scale<objects::mixins::full_scale_2d>();

        screen_stage->elements.push_back(point.get());
        if(screen_stage->points.size() == 3)
        {
            screen_stage->elements.remove_object(screen_stage->points[0].get());
            screen_stage->points.erase(screen_stage->points.begin());
        }
        return true;
    }

    void main_menu::init_event_objects()
    {
        start_button.bind_scale<objects::mixins::full_scale_2d>(window, elements.event_manager);
        slider.bind_scale<objects::mixins::full_scale_2d, objects::mixins::coord_scale_2d_composite>(window, elements.event_manager);


        start_button.bind_press([](sf::Event event){return true;}, elements.event_manager);
        background.bind_press([this](sf::Event event) { return construct_convex_press(event, this); },
                              elements.event_manager);
        slider.bind_slider([this](sf::Event event) {
            std::cout << this->slider.get_value() << '\n';
            return true;
        }, elements.event_manager);

        drag_test.bind_drag([this](sf::Event event){
            this->drag_test.set_position(this->drag_test.get_position() + this->drag_test.get_moved_to());
            return true;
            }, elements.event_manager);
    }

}
