# CMake의 최소 버전을 명시합니다.
cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(STB_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(STB_INCLUDE "${STB_PATH}/include")
set(STB_SOURCE "${STB_PATH}/src")

file(GLOB_RECURSE STB_INCLUDE_FILE "${STB_INCLUDE}/*")
file(GLOB_RECURSE STB_SOURCE_FILE "${STB_SOURCE}/*")

add_library(stb STATIC ${STB_INCLUDE_FILE} ${STB_SOURCE_FILE})

target_include_directories(stb PUBLIC ${STB_INCLUDE})

source_group(include FILES ${STB_INCLUDE_FILE})
source_group(src FILES ${STB_SOURCE_FILE})