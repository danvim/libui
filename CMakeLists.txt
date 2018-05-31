cmake_minimum_required(VERSION 3.8)
project(libui C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp inc/*.h)
add_library(ui STATIC ${SOURCE_FILES})

set_target_properties(ui PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(ui PRIVATE inc)
target_include_directories(ui PRIVATE src)
