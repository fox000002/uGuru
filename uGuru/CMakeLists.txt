cmake_minimum_required (VERSION 2.8)
PROJECT (UGURU)

#-----------------------------------------------------------------------------
# Instructions for use : Normal Build
#
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Basic stuff here
#-----------------------------------------------------------------------------

add_subdirectory (tinyxml)

#-----------------------------------------------------------------------------
# Options
#-----------------------------------------------------------------------------
# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

OPTION (BUILD_TEST "Build test programs" OFF)
IF (BUILD_TEST)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  add_subdirectory (test)
ENDIF (BUILD_TEST)

#-----------------------------------------------------------------------------
#
#-----------------------------------------------------------------------------
add_subdirectory (src)

