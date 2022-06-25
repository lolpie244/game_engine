//
// Created by lolpie on 11/25/21.
//


namespace game
{
    using namespace std;
    using namespace sf;
    void back_press(map<string, sh_p<info::parent>>& main_info)
    {
        (new main_menu_np::main_menu(main_info))->main();
    }

    void game::init_event_objects()
    {
        new event::button(&back_button, [](){}, [this](){ back_press(*this->main_info); }, gui.event_manager);
        add_scale();
    }
}