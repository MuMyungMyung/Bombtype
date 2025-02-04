### SERVER ###

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(server ${SOURCES})

target_link_libraries(server PUBLIC compiler_flags)

target_link_libraries(server PRIVATE common)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
