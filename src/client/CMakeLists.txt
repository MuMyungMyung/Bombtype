### CLIENT ###

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(client ${SOURCES})

target_link_libraries(client PUBLIC compiler_flags common)

target_link_libraries(client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
