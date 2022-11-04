//
// Created by lolpie on 11/19/21.
//
#pragma once
// #include <type_traits>
#include <memory>
#include <unordered_map>
#include <utility>
#include "../parent_stage_class.h"
#include "../../info_classes/info.h"
#include "../../objects/includes.h"
#include "../../settings/texture.h"
#include "../../helping/includes.h"
#include "textures.h"
#include <memory>

namespace detail_bezier_np
{
    using namespace std;
    using namespace sf;
    using namespace parent_stage_class;
	using objects::parent::abstract_object;
    using helping_function::Point;

    class detail_bezier: public parent_stage
    {
    private:
    protected:
        void init_gui_objects() override
        {
            background = objects::gui::gui_object({960, 540}, {1920, 1080}, textures::background);
            slider = objects::gui::Slider({570, 995, 2}, {1100, 124}, textures::slider, {0, 1});
			bezier = make_shared<objects::figures::Bezier>(Point(0, 0, 3));

			clear_button = objects::gui::button({1600, 990, 3}, {150, 150}, textures::decline_button);
			to_draw = objects::gui::button({1330, 995, 3}, {359, 160}, textures::to_draw_button);

			with_points = objects::gui::RadioButton({1830, 990, 3}, {90, 90}, textures::blue_radio_button);
			with_helping = objects::gui::RadioButton({1730, 990, 3}, {90, 90}, textures::yellow_radio_button);

			bezier->set_max_t(0);
            elements.insert({&background, &slider, bezier.get(), &with_helping, &with_points, &clear_button, &to_draw});
        }
        void init_event_objects() override;

    public:
        objects::gui::gui_object background;
        objects::gui::Slider slider;
		objects::gui::button clear_button;
		objects::gui::button to_draw;

		sh_p<objects::figures::Bezier> bezier;

	    objects::gui::RadioButton with_points;
	    objects::gui::RadioButton with_helping;

        detail_bezier(map<string, sh_p<info::parent>>& main_info):
			parent_stage(main_info){}

		objects::figures::BezierDisplay get_current_display_type()
		{
			objects::figures::BezierDisplay display_type = objects::figures::only_curve;
			if(with_points.get_value())
				display_type = objects::figures::with_points;
			if(with_helping.get_value())
				display_type = objects::figures::with_helping_lines;
			return display_type;
		}
    };

}
