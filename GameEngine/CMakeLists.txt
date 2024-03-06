# CMake의 최소 버전을 명시합니다.
cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/jsoncpp)
add_subdirectory(ThirdParty/miniaudio)
add_subdirectory(ThirdParty/stb)
add_subdirectory(ThirdParty/imgui)

set_target_properties(glad jsoncpp miniaudio stb imgui PROPERTIES FOLDER "ThirdParty")

set(GAME_ENGINE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(GAME_ENGINE_INCLUDE "${GAME_ENGINE_PATH}/Include")
set(GAME_ENGINE_SCRIPT "${GAME_ENGINE_PATH}/Script")
set(GAME_ENGINE_SHADER "${GAME_ENGINE_PATH}/Shader")
set(GAME_ENGINE_SOURCE "${GAME_ENGINE_PATH}/Source")

file(GLOB_RECURSE GAME_ENGINE_INCLUDE_FILE "${GAME_ENGINE_INCLUDE}/**")
file(GLOB_RECURSE GAME_ENGINE_SCRIPT_FILE "${GAME_ENGINE_SCRIPT}/*")
file(GLOB_RECURSE GAME_ENGINE_SHADER_FILE "${GAME_ENGINE_SHADER}/*")
file(GLOB_RECURSE GAME_ENGINE_ENGINE_FILE "${GAME_ENGINE_SOURCE}/*")

add_library(GameEngine
    STATIC 
    ${GAME_ENGINE_INCLUDE_FILE}
    ${GAME_ENGINE_SCRIPT_FILE} 
    ${GAME_ENGINE_SHADER_FILE}
    ${GAME_ENGINE_ENGINE_FILE}
)

target_include_directories(GameEngine PUBLIC ${GAME_ENGINE_INCLUDE})
target_link_libraries(
    GameEngine 
    PUBLIC 
    Dbghelp.lib 
    Pathcch.lib
    Shlwapi.lib
    opengl32.lib
    glad
    jsoncpp
    miniaudio
    stb
    imgui
)
target_compile_definitions(
    GameEngine 
    PUBLIC
    $<$<CONFIG:Debug>:DEBUG_MODE>
    $<$<CONFIG:Release>:RELEASE_MODE>
    $<$<CONFIG:RelWithDebInfo>:REL_WITH_DEB_INFO_MODE>
    $<$<CONFIG:MinSizeRel>:MIN_SIZE_REL_MODE>
)

set_property(TARGET GameEngine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

source_group(Include FILES ${GAME_ENGINE_INCLUDE_FILE})
source_group(Script FILES ${GAME_ENGINE_SCRIPT_FILE})
source_group(Shader FILES ${GAME_ENGINE_SHADER_FILE})
source_group(Source FILES ${GAME_ENGINE_ENGINE_FILE})