cmake_minimum_required(VERSION 3.20)
project(game_engine)

set(CMAKE_CXX_STANDARD 20)
## In most cases better set in the CMake cache
##set(SFML_DIR "/usr/local/lib/cmake/SFML")
##
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
add_executable(game_engine main.cpp settings/library.h settings/project_files.h objects/figures/figure_object.h settings/texture.h helping/perfect_collision.h info_classes/info.h objects/gui/gui_object.h helping/window.h event/observer_object.h event/common_event.h settings/prototype.h stages/parent_stage_class.h helping/sat_math.h helping/sat_collision.h settings/constants_and_defines.h helping/structs.h objects/figures/convex.h objects/gui/button.h objects/gui/label.h objects/figures/bezier.h objects/parent/object.h objects/mixins/drawable/class.h objects/mixins/drawable/methods.h objects/mixins/clickable.h objects/mixins/includes.h objects/gui/includes.h event/includes.h helping/includes.h objects/figures/includes.h objects/mixins/scalable/class.h objects/mixins/scalable/class.h objects/gui/slider.h objects/mixins/scalable/methods.h objects/mixins/draggable.h objects/parent/composite_object.h objects/parent/abstract_object.h stages/detail_bezier/stage.h stages/detail_bezier/events.h stages/detail_bezier/textures.h stages/draw_bezier/stage.h stages/draw_bezier/events.h stages/draw_bezier/textures.h)
target_link_libraries(game_engine sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
##
