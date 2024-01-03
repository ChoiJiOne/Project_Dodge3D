# CMake의 최소 버전을 명시합니다.
cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CLIENT_INCLUDE "${CLIENT_PATH}/Include")
set(CLIENT_SOURCE "${CLIENT_PATH}/Source")
set(CLIENT_SCRIPT "${CLIENT_PATH}/Script")

file(GLOB_RECURSE CLIENT_INCLUDE_FILE "${CLIENT_INCLUDE}/*")
file(GLOB_RECURSE CLIENT_SOURCE_FILE "${CLIENT_SOURCE}/*")
file(GLOB_RECURSE CLIENT_SCRIPT_FILE "${CLIENT_SCRIPT}/*" )

add_executable(Client
    WIN32
    ${CLIENT_INCLUDE_FILE}
    ${CLIENT_SOURCE_FILE}
    ${CLIENT_SCRIPT_FILE}
)

target_include_directories(Client PUBLIC ${CLIENT_INCLUDE} ${GAME_ENGINE_INCLUDE})
target_link_libraries(Client PUBLIC GameEngine)

source_group(Include FILES ${CLIENT_INCLUDE_FILE})
source_group(Source FILES ${CLIENT_SOURCE_FILE})
source_group(Script FILES ${CLIENT_SCRIPT_FILE})

set(COMMANDLINE "rootPath=${CMAKE_SOURCE_DIR}/ title=Dodge3D x=200 y=200 w=800 h=600 resize=true fullscreen=false")
set_target_properties(Client PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS ${COMMANDLINE})