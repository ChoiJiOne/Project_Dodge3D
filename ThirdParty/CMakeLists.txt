cmake_minimum_required(VERSION 3.27)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(imgui)
add_subdirectory(mimalloc)
add_subdirectory(miniaudio)
add_subdirectory(sqlite3)
add_subdirectory(stb)
add_subdirectory(yaml-cpp)

set_target_properties(
    glad
    glfw
    glm
    imgui
    mimalloc-static
    miniaudio
    sqlite3
    stb
    yaml-cpp
    PROPERTIES FOLDER "ThirdParty"
)