include_directories(${PROJECT_SOURCE_DIR}/gauntcraftcore/inc)

FILE(GLOB tcsourceFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(TCSOURCES ${tcsourceFiles})
FILE(GLOB tcheaderFiles "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")
set(TCHEADERS ${tcheaderFiles})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/scripts")

add_executable(
    gauntcraft-testclient
    ${TCSOURCES}
    ${TCHEADERS}
)

target_link_libraries(
    gauntcraft-testclient
    gauntcraftcore
)

set(SERVERDIR "${CMAKE_CURRENT_BINARY_DIR}/../output/testclient")
ADD_CUSTOM_COMMAND(
    TARGET gauntcraft-testclient
    POST_BUILD
    COMMAND mkdir ${SERVERDIR}
    COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/gauntcraft-testclient ${SERVERDIR}/gauntcraft-testclient
)
