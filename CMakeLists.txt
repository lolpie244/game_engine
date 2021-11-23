cmake_minimum_required(VERSION 3.20)
project(racing)

set(CMAKE_CXX_STANDARD 20)
## In most cases better set in the CMake cache
##set(SFML_DIR "/usr/local/lib/cmake/SFML")
##
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
add_executable(racing main.cpp settings/library.h settings/project_files.h object_classes/game_object.h settings/window.h object_parameters/scale.h settings/textures.h object_parameters/draw.h stages/main_menu.h object_classes/parent_object.h helping/perfect_collision.h helping/scale.h info_classes/info.h info_classes/info_functions.h object_classes/gui_object.h object_classes/object.h helping/type_class.h)
target_link_libraries(racing sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
##
