//
// Created by lolpie on 11/25/21.
//


namespace game
{
    using namespace std;
    using namespace sf;
    void back_press(map<string, sh_p<info::parent>>& main_info)
    {
        main_menu::main(main_info);
    }
}