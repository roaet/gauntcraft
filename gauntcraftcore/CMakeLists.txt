FILE(GLOB sourceFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(SOURCES ${sourceFiles})
FILE(GLOB headerFiles "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")
set(HEADERS ${headerFiles})

#find_package(Boost REQUIRED)
#find_package(OpenGL REQUIRED)
add_library(gauntcraftcore
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(
    gauntcraftcore
    ${GLOG_LIBRARY}
)
