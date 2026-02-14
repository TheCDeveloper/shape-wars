cmake_minimum_required(VERSION 3.30)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(ShapeWars VERSION 1.0 LANGUAGES C)

find_package(SDL3 REQUIRED CONFIG)


file(GLOB SOURCES src/*.c)
add_executable(ShapeWars ${SOURCES})
target_link_libraries(ShapeWars PRIVATE SDL3::SDL3)
