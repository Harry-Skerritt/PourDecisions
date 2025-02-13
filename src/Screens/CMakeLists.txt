cmake_minimum_required(VERSION 3.16)
project(Screens)


# Set the source files for the options menu
set(SOURCE_FILES
    OptionsScreen.h
    OptionsScreen.cpp
    PlayerSetup.h
    PlayerSetup.cpp
    MainGame.h
    MainGame.cpp
    ForfeitScreen.h
    ForfeitScreen.cpp
    Menus/PauseMenu.h
    Menus/PauseMenu.cpp
    Menus/GameOver.h
    Menus/GameOver.cpp
    LoadingScreen.h
    LoadingScreen.cpp 
    HTPScreen.h
    HTPScreen.cpp
    Credits.h
    Credits.cpp
)

# Add a library or an object file for the options menu (if it's a separate module)
# You can choose to create a static library or simply compile as part of the executable.

add_library(Screens STATIC ${SOURCE_FILES})

# Link SFML libraries to the OptionsMenu if needed
target_link_libraries(Screens PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

# If you have other dependencies for the Options Menu, link them here as well
# target_link_libraries(OptionsMenu PRIVATE other-library)

# Optionally, you can add compile features if needed
target_compile_features(Screens PRIVATE cxx_std_20)