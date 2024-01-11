cmake_minimum_required(VERSION 3.27)

project(ProjectA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(GameEngine)
add_subdirectory(Client)
add_subdirectory(GeometryExporter)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Client)