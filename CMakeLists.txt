cmake_minimum_required(VERSION 3.31.5)

project(Bombtype VERSION 1.0)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(compiler_flags INTERFACE
                      "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
                      "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
                      )

##############
#   CLIENT   #
##############

file(GLOB_RECURSE CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/client/*.cpp")
add_executable(client ${CLIENT_SOURCES})
target_link_libraries(client PUBLIC compiler_flags)
target_link_libraries(client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/client)

##############
#   SERVER   #
##############

file(GLOB_RECURSE SERVER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/server/*.cpp")
add_executable(server ${SERVER_SOURCES})
target_link_libraries(server PUBLIC compiler_flags)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/server)
