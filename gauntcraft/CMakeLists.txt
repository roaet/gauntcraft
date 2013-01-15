cmake_minimum_required(VERSION 2.8)
project(gauntcraft)
subdirs(gauntcraft libs)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../bin")

set (SDL_FOLDER ${gauntcraft_SOURCE_DIR}/libs/SDL-1.2.15
    CACHE STRING "Path to SDL 1.2.15" FORCE)
set (SDLIMAGE_FOLDER ${gauntcraft_SOURCE_DIR}/libs/SDL_image-1.2.12
    CACHE STRING "Path to SDL_image 1.2.12" FORCE)
set (SDLCONFIG ${SDL_FOLDER}/local/bin/sdl-config)
#find_package(SDL REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)

add_definitions(`${SDLCONFIG} --cflags`)
IF(WIN32)
    SET(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
ELSE(WIN32)
    SET(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
ENDIF(WIN32)

find_library(SDL_LIBRARY
    NAMES SDL
    PATHS ${SDL_FOLDER}
    PATH_SUFFIXES local/lib VisualC/SDL/Release
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_DEFAULT_PATH
)
find_library(SDLMAIN_LIBRARY
    NAMES SDLmain SDL_main
    PATHS ${SDL_FOLDER}
    PATH_SUFFIXES local/lib VisualC/SDLmain/Release
)
find_library(SDLIMAGE_LIBRARY
    NAMES SDL_image
    PATHS ${SDLIMAGE_FOLDER}
    PATH_SUFFIXES local/lib
    NO_DEFAULT_PATH
)
include_directories(
    ${gauntcraft_SOURCE_DIR}/gauntcraft/inc
    ${gauntcraft_SOURCE_DIR}/libs/SDL_gfxPrimitives
    ${SDL_FOLDER}/local/include
    ${SDLIMAGE_FOLDER}/local/include
)

