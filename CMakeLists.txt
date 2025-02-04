cmake_minimum_required(VERSION 3.31.5)

project(Bombtype VERSION 1.0)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,GNU,ARMClang,AppleClang,Clang,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(compiler_flags INTERFACE
                      "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
                      "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
                      )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

##############
#   COMMON   #
##############
add_subdirectory(src/common)

##############
#   CLIENT   #
##############
add_subdirectory(src/client)

##############
#   SERVER   #
##############
add_subdirectory(src/server)
