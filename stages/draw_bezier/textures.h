//
// Created by lolpie on 10/22/22.
//
#pragma once
#include "../../settings/texture.h"
#include "../../helping/structs.h"
#include <memory>
namespace draw_bezier_np{ namespace textures
{
    using namespace texture;
    using std::make_shared;
    using structs::Point;

    auto background = make_shared<common_texture>("textures/background.jpg");
	auto radio_button = make_shared<button>("textures/radio_released.png", "textures/radio_pressed.png");
	auto decline_button = make_shared<button>("textures/decline_released.png", "textures/decline_pressed.png");
	auto to_detail_button = make_shared<button>("textures/detail_released.png", "textures/detail_pressed.png");
}}
