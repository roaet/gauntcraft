find_library(SDLMAIN_LIBRARY
    NAMES SDLmain
)

find_package(SDL REQUIRED)
find_package(SDL_image)
find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)


set (EXTRA_LIBS "")

include_directories(
    ${gauntcraft_SOURCE_DIR}/gauntcraft/inc
    ${gauntcraft_SOURCE_DIR}/SDL_gfxPrimitives
)

file(GLOB gauntcraft_src
    *.cpp
)

set (EXTRA_LIBS ${EXTRA_LIBS} SDL_gfxPrimitives)

add_executable(gauntcraft ${gauntcraft_src})

target_link_libraries(
    gauntcraft
    ${OPENGL_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLMAIN_LIBRARY}
    ${EXTRA_LIBS}
)
