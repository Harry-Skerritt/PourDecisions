cmake_minimum_required(VERSION 3.26)
project(PourDecisions LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(SOURCE_FILES src/main.cpp)

add_executable(PourDecisions ${SOURCE_FILES})
target_compile_features(PourDecisions PRIVATE cxx_std_17)
target_link_libraries(PourDecisions PRIVATE SFML::Graphics)
