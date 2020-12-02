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
find_package( Qt5 COMPONENTS Widgets Svg REQUIRED )
# find_package( jsoncpp CONFIG REQUIRED )
find_package( HIDAPI CONFIG REQUIRED )

# Specify Include Directories
include_directories( ${Qt5Widgets_INCLUDES} )
# include_directories( ${jsoncpp_INCLUDE_DIRS} )
include_directories( ${HIDAPI_INCLUDE_DIR} )

# Additional Library Directories
# link_directories( ${jsoncpp_LIB_DIR} )
# target_link_directories( ${HIDAPI_LIBRARY} )
find_library( JOYSHOCK_LIBRARIES NAMES JoyShockLibrary JoyShockLibrary.dll PATHS ${CMAKE_CURRENT_SOURCE_DIR}/dep)

# INCLUDE(FindFreetype)
# IF(NOT FREETYPE_FOUND)
#   FIND_LIBRARY(FREETYPE_LIBRARIES NAMES libfreetype freetype.dll PATHS "./libs/MacOS" "./libs/Windows" DOC "Freetype library")
#   FIND_PATH(FREETYPE_INCLUDE_DIRS ftbuild.h "./includes" DOC "Freetype includes")
# ENDIF(NOT FREETYPE_FOUND)
# INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
# TARGET_LINK_LIBRARIES(MyProject ${FREETYPE_LIBRARIES})

# Define source files to compile
file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_SOURCE_DIR}/libs/* ${CMAKE_CURRENT_SOURCE_DIR}/forms/* )

# Add executable
add_executable( overlay ${SRCFILES} )

# Link libraries
# target_link_libraries( overlay PRIVATE Qt5::Widgets Qt5::Svg ${HIDAPI_LIBRARY} )
target_link_libraries( overlay PRIVATE Qt5::Widgets Qt5::Svg ${HIDAPI_LIBRARY} ${JOYSHOCK_LIBRARIES} )
target_include_directories( overlay PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include )