find_package(SDL REQUIRED)
find_package(SDL_image)
find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)

find_library(SDLMAIN_LIBRARY
    NAMES SDLmain SDL_main
    PATH_SUFFIXES local/lib VisualC/SDLmain/Release
)

set (EXTRA_LIBS "")

include_directories(
    ${gauntcraft_SOURCE_DIR}/gauntcraft/inc
    ${gauntcraft_SOURCE_DIR}/SDL_gfxPrimitives
)

file(GLOB gauntcraft_src
    *.cpp
)

set (EXTRA_LIBS ${EXTRA_LIBS} SDL_gfxPrimitives)

if (APPLE)
    set(EXTRA_LIBS ${EXTRA_LIBS} "-framework Cocoa")
endif()

add_executable(
    gauntcraft 
    WIN32
    MACOSX_BUNDLE
    ${gauntcraft_src}
)

target_link_libraries(
    gauntcraft
    ${OPENGL_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLMAIN_LIBRARY}
    ${EXTRA_LIBS}
)

if(APPLE)
    set(BUNDLE_BINARY
        ${CMAKE_CURRENT_BINARY_DIR}/HelloSDL.app/Contents/MacOS/HelloSDL)
    add_custom_command(TARGET HelloSDL POST_BUILD
        COMMAND python scripts/frameworkify.py ${BUNDLE_BINARY}
        ${SDL_LIBRARY})
endif()
