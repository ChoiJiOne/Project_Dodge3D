cmake_minimum_required(VERSION 3.27)

project(DodgeBall)

set(PROJECT_NAME "DodgeBall")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/jsoncpp)
add_subdirectory(ThirdParty/miniaudio)
add_subdirectory(ThirdParty/stb)
add_subdirectory(ThirdParty/imgui)

set_target_properties(glad jsoncpp miniaudio stb imgui PROPERTIES FOLDER "ThirdParty")

add_subdirectory(${PROJECT_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# set_target_properties(Dodge3D PROPERTIES LINK_FLAGS "/level='requireAdministrator' /uiAccess='false'")
# set(CPACK_GENERATOR "NSIS")
# set(CPACK_NSIS_MUI_ICON ${CMAKE_CURRENT_SOURCE_DIR}/Dodge3D/Resource/Icon/Icon.ico)
# set(CPACK_NSIS_MUI_UNIICON ${CMAKE_CURRENT_SOURCE_DIR}/Dodge3D/Resource/Icon/Icon.ico)

# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/GameEngine/Shader DESTINATION GameEngine)
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Dodge3D/Resource DESTINATION Dodge3D)
# install(TARGETS Dodge3D DESTINATION .)

# set(CPACK_PACKAGE_NAME "Dodge3D")
# set(CPACK_PACKAGE_VERSION "0.0.0")
# set(CPACK_PACKAGE_VENDOR "Github-ChoiJiOne")
# set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "https://github.com/ChoiJiOne/ProjectA_Dodge3D")
# set(CPACK_PACKAGE_INSTALL_DIRECTORY "Dodge3D")
# set(CPACK_PACKAGE_EXECUTABLES "Dodge3D" "Dodge3D")

# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")

# include(CPack)