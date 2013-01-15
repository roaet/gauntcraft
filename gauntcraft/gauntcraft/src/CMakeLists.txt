set (EXTRA_LIBS "")


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

#link_libraries(
#    SGE `${SDLCONFIG} --static-libs`
#)

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
