#
# This module is designed to find/handle the clingo library
#
# Requirements:
# - CMake >= 2.8.7 (for new version of find_package_handle_standard_args)
#
# The following variables will be defined for your use:
#   - CLINGO_FOUND            : if false, do not try to link to clingo 
#   - CLINGO_INCLUDE_DIR      : clingo include directory
#   - CLINGO_LIBRARY          : clingo libraries
#   - CLINGO_VERSION          : complete version of clingo (x.y.z)
#   - CLINGO_MAJOR_VERSION    : major version of clingo
#   - CLINGO_MINOR_VERSION    : minor version of clingo
#   - CLINGO_REVISION_VERSION : revision version of clingo
#
# How to use:
#   1) Copy this file in the root of your project source directory
#   2) Then, tell CMake to search this non-standard module in your project directory by adding to your CMakeLists.txt:
#        set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
#   3) Finally call find_package( clingo ) once
#
# Here is a complete sample to build an executable:
#
#   set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR} )
#
#   find_package( clingo REQUIRED ) # Note: name is case sensitive
#
#   include_directories( ${CLINGO_INCLUDE_DIR} )
#   add_executable( myapp myapp.c )
#   target_link_libraries( myapp ${CLINGO_LIBRARY} )
#


#=============================================================================
# Copyright (c) 2014, aiq
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#=============================================================================

cmake_minimum_required( VERSION 2.8.7 )

########## Private ##########
if( NOT DEFINED CLINGO_PUB_NS )
   set( CLINGO_PUB_NS "CLINGO" )
endif( NOT DEFINED CLINGO_PUB_NS )

if( NOT DEFINED CLINGO_PRIV_VAR_NS)
   set( CLINGO_PRIV_VAR_NS "_${CLINGO_PUB_NS}" )
endif( NOT DEFINED CLINGO_PRIV_VAR_NS )

function( clingo_debug _VARNAME )
   if( ${CLINGO_PUB_NS}_DEBUG )
      if( DEFINED ${CLINGO_PUB_NS}_${_VARNAME} )
         message( "${CLINGO_PUB_NS}_${_VARNAME} = ${${CLINGO_PUB_NS}_${_VARNAME}}" )
      else( DEFINED ${CLINGO_PUB_NS}_${_VARNAME} )
         message( "${CLINGO_PUB_NS}_${_VARNAME} = <UNDEFINED>" )
      endif( DEFINED ${CLINGO_PUB_NS}_${_VARNAME} )
   endif( ${CLINGO_PUB_NS}_DEBUG )
endfunction( clingo_debug )

########## Public ##########
find_path(
   ${CLINGO_PUB_NS}_INCLUDE_DIR
   NAMES "clingo.h"
   PATH_SUFFIXES "include"
)

if( ${CLINGO_PUB_NS}_INCLUDE_DIR )

   find_library(
      ${CLINGO_PUB_NS}_LIBRARY
      NAMES clingo
   )

   file( READ "${${CLINGO_PUB_NS}_INCLUDE_DIR}/clingo/version.h" ${CLINGO_PRIV_VAR_NS}_H_CONTENT )
   string( REGEX REPLACE ".*# *define *CLINGO_VER_MAJOR *([0-9]+).*" "\\1"
           ${CLINGO_PUB_NS}_MAJOR_VERSION
           ${${CLINGO_PRIV_VAR_NS}_H_CONTENT} )
   string( REGEX REPLACE ".*# *define *CLINGO_VER_MINOR *([0-9]+).*" "\\1"
           ${CLINGO_PUB_NS}_MINOR_VERSION
           ${${CLINGO_PRIV_VAR_NS}_H_CONTENT} )
   string( REGEX REPLACE ".*# *define *CLINGO_VER_REVISION *([0-9]+).*" "\\1"
           ${CLINGO_PUB_NS}_REVISION_VERSION
           ${${CLINGO_PRIV_VAR_NS}_H_CONTENT} )
   set( ${CLINGO_PUB_NS}_VERSION
        "${${CLINGO_PUB_NS}_MAJOR_VERSION}.${${CLINGO_PUB_NS}_MINOR_VERSION}.${${CLINGO_PUB_NS}_REVISION_VERSION}" )

   include( FindPackageHandleStandardArgs )
   if( ${CLINGO_PUB_NS}_FIND_REQUIRED AND NOT ${CLINGO_PUB_NS}_FIND_QUIETLY )
      find_package_handle_standard_args(
         ${CLINGO_PUB_NS}
         REQUIRED_VARS ${CLINGO_PUB_NS}_LIBRARY ${CLINGO_PUB_NS}_INCLUDE_DIR
         VERSION_VAR ${CLINGO_PUB_NS}_VERSION
      )
   else( ${CLINGO_PUB_NS}_FIND_REQUIRED AND NOT ${CLINGO_PUB_NS}_FIND_QUIETLY )
      find_package_handle_standard_args(
         ${CLINGO_PUB_NS}
         "clingo not found" ${CLINGO_PUB_NS}_LIBRARY ${CLINGO_PUB_NS}_INCLUDE_DIR
      )
   endif( ${CLINGO_PUB_NS}_FIND_REQUIRED AND NOT ${CLINGO_PUB_NS}_FIND_QUIETLY )

else( ${CLINGO_PUB_NS}_INCLUDE_DIR )
   if( ${CLINGO_PUB_NS}_FIND_REQUIRED AND NOT ${CLINGO_PUB_NS}_FIND_QUIETLY )
      message( FATAL_ERROR "Could not find clingo include directory" )
   endif( ${CLINGO_PUB_NS}_FIND_REQUIRED AND NOT ${CLINGO_PUB_NS}_FIND_QUIETLY )
endif( ${CLINGO_PUB_NS}_INCLUDE_DIR )

mark_as_advanced(
   ${CLINGO_PUB_NS}_INCLUDE_DIR
   ${CLINGO_PUB_NS}_LIBRARY
)

# IN (args)
clingo_debug("FIND_REQUIRED")
clingo_debug("FIND_QUIETLY")
clingo_debug("FIND_VERSION")
# OUT
# Linking
clingo_debug("INCLUDE_DIRS")
clingo_debug("LIBRARIES")
# Version
clingo_debug("MAJOR_VERSION")
clingo_debug("MINOR_VERSION")
clingo_debug("REVISION_VERSION")
clingo_debug("VERSION")
