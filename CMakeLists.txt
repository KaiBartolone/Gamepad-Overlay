# Start
cmake_minimum_required( VERSION 3.1 )
project( overlay )

# Set flags for qt5 forms
set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

# Set flag standards for qt5
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Find packages
find_package( Qt5 COMPONENTS Widgets Svg Gamepad REQUIRED )

# Specify Include Directories
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Qt5Widgets_INCLUDES} )

# Additional Library Directories
link_directories( ${OpenCV_LIB_DIR} )

# Define source files to compile
file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_SOURCE_DIR}/libs/* ${CMAKE_CURRENT_SOURCE_DIR}/forms/* )

# Add executable
add_executable( overlay ${SRCFILES} )

# Link libraries
target_link_libraries( overlay PRIVATE Qt5::Widgets Qt5::Svg Qt5::Gamepad )
target_include_directories( overlay PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include )