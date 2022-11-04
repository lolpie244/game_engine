//
// Created by lolpie on 11/19/21.
//
#pragma once
#include <utility>
#include "../parent_stage_class.h"
#include "../../info_classes/info.h"
#include "../../objects/includes.h"
#include "../../settings/texture.h"
#include "../../helping/includes.h"
#include "textures.h"

namespace draw_bezier_np
{
    using namespace std;
    using namespace sf;
    using namespace parent_stage_class;
	using objects::parent::abstract_object;
    using helping_function::Point;

    class draw_bezier: public parent_stage
    {
    private:
    protected:
        void init_gui_objects() override
        {
            background = objects::gui::gui_object({960, 540}, {1920, 1080}, textures::background);
			next_bezier = objects::figures::Bezier({0, 0, 3}, objects::figures::with_points, 2, sf::Color::Blue);
			next_bezier.set_draw<objects::mixins::ObjectCommonDraw, objects::figures::BezierDraw>();

			radio_button = objects::gui::RadioButton({1830, 990, 3}, {90, 90}, textures::radio_button);
			clear_button = objects::gui::button({1690, 990, 3}, {150, 150}, textures::decline_button);
			to_detail = objects::gui::button({1400, 995, 3}, {359, 160}, textures::to_detail_button);
			elements.insert({&background, &next_bezier, &radio_button, &to_detail, &clear_button});
        }
        void init_event_objects() override;
		void after_events() override
		{
			if(beziers.empty())
				return;
			auto mouse = helping_function::get_mouse_position(*window);
			if(!background.get_is_pressed())
				next_bezier.push_back(mouse);
			else if(last_bezier()->points_count() >= 3)
				last_bezier()->insert((Point)*last_bezier()->last_point() - (mouse - *last_bezier()->last_point()), 2);
		}
       	void after_iteration() override
		{
			if(beziers.empty())
				return;
			if(!background.get_is_pressed())
				next_bezier.pop_back();
			else if (last_bezier()->points_count() >= 3)
				last_bezier()->erase(2);
		}

    public:
		bool is_first_point = true;
        objects::gui::gui_object background;
		objects::gui::button clear_button;
		objects::gui::button to_detail;

		vector<sh_p<objects::figures::Bezier>> beziers;
		objects::figures::Bezier next_bezier;
		objects::gui::RadioButton radio_button;

        vector<sh_p<objects::figures::figure_object>> points;
        draw_bezier(map<string, sh_p<info::parent>>& main_info):
                parent_stage(main_info){}


		sh_p<objects::figures::Bezier> last_bezier()
		{
			return beziers[beziers.size() - 1];
		}
		objects::figures::BezierDisplay get_current_display_type()
		{
			objects::figures::BezierDisplay display_type = objects::figures::only_curve;
			if(radio_button.get_value())
				display_type = objects::figures::with_points;
			return display_type;
		}
    };

}
