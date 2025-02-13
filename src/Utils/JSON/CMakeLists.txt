cmake_minimum_required(VERSION 3.16)
project(JSON)


# Set the source files for the options menu
set(SOURCE_FILES
	Settings.h
	Settings.cpp
	CardParser.h
	CardParser.cpp
	CardImporter.h
	CardImporter.cpp
	ForfeitParser.h
	ForfeitParser.cpp
	ForfeitImporter.h
	ForfeitImporter.cpp
)

# Add a library or an object file for the options menu (if it's a separate module)
# You can choose to create a static library or simply compile as part of the executable.

add_library(JSON STATIC ${SOURCE_FILES})

# Link SFML libraries to the OptionsMenu if needed
target_link_libraries(JSON PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)


# If you have other dependencies for the Options Menu, link them here as well
# target_link_libraries(OptionsMenu PRIVATE other-library)

# Optionally, you can add compile features if needed
target_compile_features(JSON PRIVATE cxx_std_20)