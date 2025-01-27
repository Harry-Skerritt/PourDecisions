cmake_minimum_required(VERSION 3.16)
project(PourDecisions)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Define the app version
set(APP_VERSION "pre-1.0.2")

#---- Fetch SFML, only works if you have git installed on your machine ----#
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b
)
FetchContent_MakeAvailable(SFML)

#---- File management & .exe creation ----#
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h)
add_subdirectory("src/Managers")
add_subdirectory("src/VisualAddons")
add_subdirectory("src/Utils")
add_subdirectory("src/Screens")
add_subdirectory("src/Utils/Widgets")
add_subdirectory("src/Utils/JSON")
add_subdirectory("src/GameObjects")

add_executable(PourDecisions ${SOURCE_FILES})

# Link Custom Libs
target_link_libraries(PourDecisions PRIVATE Managers VisualAddons Utils Screens Widgets JSON GameObjects)

# Link SFML
target_link_libraries(PourDecisions PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
target_compile_features(PourDecisions PRIVATE cxx_std_20)

include_directories(${CMAKE_SOURCE_DIR}/externals/json)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Cards/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Cards/)

if(WIN32)
    add_custom_command(
        TARGET PourDecisions
        COMMENT "Copy OpenAL DLL to build directory so app can have sound"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PourDecisions>
        VERBATIM)
endif()

#---- CPack NSIS Installer Configuration ----#
include(CPack)

set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_NAME "Pour Decisions")
set(CPACK_PACKAGE_VENDOR "Harry Skerritt")
set(CPACK_PACKAGE_VERSION ${APP_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Pour Decisions - The Spinwheel Drinking Game! Spin, Sip, See what happens!")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "PourDecisions")
set(CPACK_NSIS_DISPLAY_NAME "Pour Decisions Game")
set(CPACK_NSIS_MODIFY_PATH ON) # Adds app to PATH if needed
set(CPACK_NSIS_URL_INFO_ABOUT "https://harry-skerritt.itch.io/pour-decisions")
set(CPACK_NSIS_MUI_ICON ${CMAKE_CURRENT_SOURCE_DIR}/Data/Assets/icon.ico) # Optional: Add an installer icon

# Remove old files (optional, for cleanup)
set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
    "Delete /r \"$INSTDIR\\OldVersionFiles/*\"")

# Files to install
install(TARGETS PourDecisions DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data DESTINATION bin/Data)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Cards DESTINATION bin/Cards)
install(FILES ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll DESTINATION bin)

# Generate installer
cpack_add_install_type("Full")
cpack_add_component_group("Main")
cpack_add_component("Application" GROUP "Main" DESCRIPTION "PourDecisions Main Application")