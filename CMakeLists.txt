# Passes Windows and Mac -> Linux missing OpenAL
cmake_minimum_required(VERSION 3.16)
project(PourDecisions)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

#---- Fetch SFML, only works if you have git installed on your machine ----#

include(FetchContent)   # Allows fetching content remotely at configure time
FetchContent_Declare(   # Fetches SFML from github and puts it in the build directory
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b    # Makes sure to fetch SFML version 2.6.1
)

FetchContent_MakeAvailable(SFML)    # Makes sure SFML and its dependencies are avaiable for the project

#---- File management & .exe creation ----#

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h)  # Sets variable SOURCE_FILES to hold names & locations of files that need to be compiled into the application
add_subdirectory("src/Managers")
add_subdirectory("src/VisualAddons")
add_subdirectory("src/Utils")
add_subdirectory("src/Screens")
add_subdirectory("src/Utils/Widgets")

add_executable(PourDecisions ${SOURCE_FILES})  # Names the application and tells compiler which source files to use

target_link_libraries(PourDecisions PRIVATE Managers)
target_link_libraries(PourDecisions PRIVATE VisualAddons)
target_link_libraries(PourDecisions PRIVATE Utils)
target_link_libraries(PourDecisions PRIVATE Screens)
target_link_libraries(PourDecisions PRIVATE Widgets)
target_link_libraries(PourDecisions PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio) # Links the SFML libraries we need to our application
target_compile_features(PourDecisions PRIVATE cxx_std_20)  # Defines which standard of C++ the compiler should use

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)  # Copies data from source directory to build directory (so the executable can access it)

if(WIN32)
    add_custom_command(
        TARGET PourDecisions
        COMMENT "Copy OpenAL DLL to build directory so app can have sound"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PourDecisions>
        VERBATIM)
endif()