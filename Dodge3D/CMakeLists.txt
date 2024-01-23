# CMake의 최소 버전을 명시합니다.
cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DODGE_3D_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(DODGE_3D_INCLUDE ${DODGE_3D_PATH}/Include)
set(DODGE_3D_SOURCE ${DODGE_3D_PATH}/Source)

set(DODGE_3D_ICON_PATH "${DODGE_3D_PATH}/Resource/Icon/Icon.ico")
configure_file(
    "${DODGE_3D_INCLUDE}/ResourceScript.rc.in"
    "${DODGE_3D_INCLUDE}/ResourceScript.rc"
)

configure_file(
    "${DODGE_3D_INCLUDE}/Config.h.in"
    "${DODGE_3D_INCLUDE}/Config.h"
)

file(GLOB_RECURSE DODGE_3D_INCLUDE_FILE "${DODGE_3D_INCLUDE}/*")
file(GLOB_RECURSE DODGE_3D_SOURCE_FILE "${DODGE_3D_SOURCE}/*")
add_executable(Dodge3D ${DODGE_3D_INCLUDE_FILE} ${DODGE_3D_SOURCE_FILE})

target_include_directories(Dodge3D PUBLIC ${DODGE_3D_INCLUDE})

source_group(Include FILES ${DODGE_3D_INCLUDE_FILE})
source_group(Source FILES ${DODGE_3D_SOURCE_FILE})

set_target_properties(Dodge3D PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "${CMAKE_SOURCE_DIR}/")