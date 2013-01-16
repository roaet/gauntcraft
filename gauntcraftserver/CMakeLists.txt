include_directories(${PROJECT_SOURCE_DIR}/gauntcraftcore/inc)

FILE(GLOB serversourceFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(SERVERSOURCES ${serversourceFiles})
FILE(GLOB serverheaderFiles "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")
set(SERVERHEADERS ${serverheaderFiles})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/scripts")

add_executable(
    gauntcraftserver
    ${SERVERSOURCES}
    ${SERVERHEADERS}
)

target_link_libraries(
    gauntcraftserver
    gauntcraftcore
)

set(SERVERDIR "${CMAKE_CURRENT_BINARY_DIR}/../output/server")
ADD_CUSTOM_COMMAND(
    TARGET gauntcraftserver
    POST_BUILD
    COMMAND mkdir ${SERVERDIR}
    COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/gauntcraftserver ${SERVERDIR}/gauntcraftserver
)
