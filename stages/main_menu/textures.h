//
// Created by lolpie on 10/22/22.
//
#pragma once
#include "../../settings/texture.h"
#include "../../helping/structs.h"
namespace main_menu_np::textures
{
    using namespace texture;
    using std::make_shared;
    using structs::Point;

    auto background = make_shared<common_texture>("textures/background.jpg");
    auto dot = make_shared<common_texture>("textures/dot.png");

    auto texture = make_shared<common_texture>("textures/restart.png");
    auto test_button = make_shared<button>("textures/blue_ok_released.png", "textures/blue_ok_pressed.png");

    auto test_slider = make_shared<slider>("textures/slider.png", "textures/picker.png", Point({45, 37}), Point({636, 37}));
}
