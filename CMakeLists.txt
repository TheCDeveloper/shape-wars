cmake_minimum_required(VERSION 3.30)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(ShapeWars VERSION 1.0 LANGUAGES C)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)


file(GLOB SOURCES CONFIGURE_DEPENDS src/*.c)
add_executable(ShapeWars ${SOURCES})
target_link_libraries(ShapeWars PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf m)
