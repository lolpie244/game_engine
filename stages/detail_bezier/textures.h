//
// Created by lolpie on 10/22/22.
//
#pragma once
#include "../../settings/texture.h"
#include "../../helping/structs.h"
namespace detail_bezier_np{ namespace textures
{
    using namespace texture;
    using std::make_shared;
    using structs::Point;

    auto background = make_shared<common_texture>("textures/background.jpg");

    auto slider = make_shared<texture::slider>("textures/slider.png", "textures/picker.png", Point({45, 37}), Point({636, 37}));

	auto blue_radio_button = make_shared<button>("textures/radio_released.png", "textures/radio_pressed.png");
	auto yellow_radio_button = make_shared<button>("textures/radio_released.png", "textures/radio_pressed_yellow.png");

	auto decline_button = make_shared<button>("textures/decline_released.png", "textures/decline_pressed.png");
	auto to_draw_button = make_shared<button>("textures/draw_released.png", "textures/draw_pressed.png");
}}
