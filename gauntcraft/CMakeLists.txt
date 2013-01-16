cmake_minimum_required(VERSION 2.8)
project(gauntcraft)
subdirs(gauntcraft)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../bin")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/scripts")

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_gfx REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)

find_library(SDLMAIN_LIBRARY
    NAMES SDLmain
    PATHS /usr/local/lib
)

include_directories(
    ${gauntcraft_SOURCE_DIR}/gauntcraft/inc
)
