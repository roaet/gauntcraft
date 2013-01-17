cmake_minimum_required(VERSION 2.8)
project (gauntcraft)

add_subdirectory(gauntcraftcore)
add_subdirectory(gauntcraftserver)
add_subdirectory(gauntcraft-testclient)
include_directories(${PROJECT_SOURCE_DIR}/gauntcraftcore/inc)

FILE(GLOB sourceFiles "gauntcraft/src/*.cpp")
set(SOURCES ${sourceFiles})
FILE(GLOB headerFiles "gauntcraft/inc/*.h")
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
    gauntcraftcore
    ${OPENGL_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLGFX_LIBRARY}
    ${SDLMAIN_LIBRARY}
    ${EXTRA_LIBS}
)

set(CLIENTDIR "${CMAKE_CURRENT_BINARY_DIR}/output/client")
ADD_CUSTOM_COMMAND(
    TARGET gauntcraft
    PRE_BUILD
    COMMAND mkdir ${CMAKE_CURRENT_BINARY_DIR}/output
)

ADD_CUSTOM_COMMAND(
    TARGET gauntcraft
    POST_BUILD
    COMMAND mkdir ${CLIENTDIR}
    COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/gauntcraft ${CLIENTDIR}/gauntcraft
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/gauntcraft/assets ${CLIENTDIR}/assets
)
