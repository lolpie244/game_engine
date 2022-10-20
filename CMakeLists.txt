cmake_minimum_required(VERSION 3.20)
project(game_engine)

set(CMAKE_CXX_STANDARD 20)
## In most cases better set in the CMake cache
##set(SFML_DIR "/usr/local/lib/cmake/SFML")
##
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
add_executable(racing main.cpp settings/library.h settings/project_files.h object_classes/game_objects.h object_parameters/scale.h settings/pre_loaded.h object_parameters/draw.h stages/main_menu/main_menu.h object_classes/parent_object.h helping/perfect_collision.h info_classes/info.h object_classes/gui_objects.h object_classes/object.h helping/window.h event/observer_object.h event/common_event.h stages/main_menu/events.h event/button_event.h settings/prototype.h stages/parent_stage_class.h helping/math.h helping/sat_collision.h settings/constants_and_defines.h helping/structs.h object_classes/convex_object.h object_parameters/move.h)
target_link_libraries(racing sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
##
