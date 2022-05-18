cmake_minimum_required(VERSION 2.8)
project(game_of_life)

set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(unity/src)
set(CMAKE_C_FLAGS "-std=c99")

add_executable(gameoflife main.c init.c input.c draw.c game_logic.c)
#add_executable(unit_tests unit_tests.c game_logic.c unity/src/unity.c)

target_link_libraries(gameoflife ${SDL2_LIBRARIES} SDL2_ttf)

