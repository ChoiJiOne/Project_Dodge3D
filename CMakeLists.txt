cmake_minimum_required(VERSION 3.27)

project(DodgeBall)

set(PROJECT_NAME "DodgeBall")
set(PROJECT_VERSION "Release-OpenGL")

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

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/level='requireAdministrator' /uiAccess='false'")
set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "Github-ChoiJiOne")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "https://github.com/ChoiJiOne/DodgeBall")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} ${PROJECT_NAME})
set(CPACK_NSIS_MUI_ICON ${CMAKE_CURRENT_SOURCE_DIR}\\\\Resource\\\\Icon\\\\Icon.ico)
set(CPACK_NSIS_MUI_UNIICON ${CMAKE_CURRENT_SOURCE_DIR}\\\\Resource\\\\Icon\\\\Icon.ico)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")

set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
  CreateShortCut '$DESKTOP\\\\${PROJECT_NAME}.lnk' '$INSTDIR\\\\${PROJECT_NAME}.exe'
  CreateShortCut '$SMPROGRAMS\\\\${PROJECT_NAME}\\\\${PROJECT_NAME}.lnk' '$INSTDIR\\\\${PROJECT_NAME}.exe'
")

set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
  Delete '$DESKTOP\\\\${PROJECT_NAME}.lnk'
  Delete '$SMPROGRAMS\\\\${PROJECT_NAME}\\\\${PROJECT_NAME}.lnk'
  RMDir '$SMPROGRAMS\\\\${PROJECT_NAME}'
")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Shader DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Resource DESTINATION .)
install(TARGETS ${PROJECT_NAME} DESTINATION .)

include(CPack)