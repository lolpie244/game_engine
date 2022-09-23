//
// Created by lolpie on 11/25/21.
//



namespace main_menu_np
{
    using namespace std;
    using namespace sf;
    bool construct_convex_press(sf::Event event, main_menu* screen_stage)
    {
        Point mouse = get_scaled_mouse_position(*screen_stage->window);
        screen_stage->convexes[screen_stage->current_convex].points.push_back(get_mouse_position(*screen_stage->window));
        auto point = new object(pre_loaded::dot.get(), Rect<float>(mouse.x, mouse.y, 0.5, 0.5),
                                new full_scale, new common_draw, new common_move);
        screen_stage->elements.push_back(point);
        screen_stage->convexes_points[screen_stage->current_convex].push_back(point);
        return true;
    }

    bool add_button_pressed(main_menu* screen_stage);

    bool ok_button_pressed(main_menu* screen_stage)
    {
        int event_id = sf::Event::MouseButtonPressed;
        screen_stage->elements.event_manager.remove_event(event_id, &screen_stage->background);
        screen_stage->main_button.set_textures(pre_loaded::green_plus_released.get(),
                                               pre_loaded::green_plus_pressed.get());
        screen_stage->current_convex += 1;
        if (screen_stage->current_convex == 1) {
            new events::button_event(&screen_stage->main_button, []() {},
                                     [screen_stage]() { return add_button_pressed(screen_stage); },
                                     screen_stage->elements.event_manager);
            return true;
        }
        screen_stage->main_button.is_active = false;
        auto first_convex = screen_stage->convexes[0].points;
        auto second_convex = screen_stage->convexes[1].points;
        srand(time(0));
        Point first_point = first_convex[rand() % first_convex.size()];
        Point second_point = second_convex[rand() % second_convex.size()];
        double k = helping_function::pifagor(first_point, second_point);
        Point speed = { 2 * (second_point.x - first_point.x) / k, 2 * (second_point.y - first_point.y) / k};
        screen_stage->convexes[0].speed = speed;
        for(object* points: screen_stage->convexes_points[0])
            points->speed = speed;
    }
    bool add_button_pressed(main_menu* screen_stage)
    {
        screen_stage->elements.event_manager.bind_event(sf::Event::MouseButtonPressed,
                                          [screen_stage](sf::Event event){return construct_convex_press(event, screen_stage);}, &screen_stage->background);
        if(screen_stage->current_convex == 0)
            screen_stage->main_button.set_textures(pre_loaded::blue_ok_released.get(), pre_loaded::blue_ok_pressed.get());
        else
            screen_stage->main_button.set_textures(pre_loaded::green_ok_released.get(), pre_loaded::green_ok_pressed.get());
        new events::button_event(&screen_stage->main_button, [](){}, [screen_stage](){return ok_button_pressed(screen_stage);}, screen_stage->elements.event_manager);


    }

    void main_menu::init_event_objects()
    {
        new events::button_event(&main_button, [](){}, [this](){return add_button_pressed(this);}, elements.event_manager);

    }

}
