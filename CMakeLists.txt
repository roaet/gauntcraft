cmake_minimum_required(VERSION 2.8)
project (gauntcraft)
FILE(GLOB sourceFiles "Gauntcraft/src/*.cpp")
set(SOURCES ${sourceFiles})
FILE(GLOB headerFiles "Gauntcraft/inc/*.h")
set(HEADERS ${headerFiles})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/scripts")

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_gfx REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)

add_definitions(`sdl-config --cflags --libs`)

add_executable(
    gauntcraft
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(
    gauntcraft
    ${OPENGL_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLGFX_LIBRARY}
    ${SDLMAIN_LIBRARY}
    ${EXTRA_LIBS}
)
