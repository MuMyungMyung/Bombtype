### COMMON ###

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(common ${SOURCES})

target_include_directories(common PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)


target_link_libraries(common PUBLIC compiler_flags)
