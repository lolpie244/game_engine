//
// Created by lolpie on 11/25/21.
//



namespace main_menu_np
{
    using namespace std;
    using namespace sf;
    void play_press(map<string, sh_p<info::parent>>& main_info)
    {
        (new game::game(main_info))->main();
    }
    void print()
    {
        cout << "flag\n";
    }
    void main_menu::init_event_objects()
    {
        new event::button(&start_button, [](){}, [this](){ play_press(*this->main_info);}, gui.event_manager);
        new event::button(&flag, [](){}, print, gui.event_manager);
        add_scale();
    }
}