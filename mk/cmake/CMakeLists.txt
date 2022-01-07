project( clingo )

# Required cmake version
cmake_minimum_required( VERSION 3.0 )
enable_testing()

set( LIB_NAME ${PROJECT_NAME} )

# where to look first for modules, before ${CMAKE_ROOT}/Modules/ is checked
set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Modules" )
set( ROOT "${CMAKE_SOURCE_DIR}/../.." )
set( DOC_DIR "${ROOR}/doc" )
set( INC_DIR "${ROOT}/inc" )
set( SRC_DIR "${ROOT}/src" )
set( TEST_DIR "${ROOT}/test")

# add definitions
include( CustomFunctions )
include( DefineCMakeDefaults )
include( DefineCompilerFlags )
include( CTest )

# file list
include( ${CMAKE_SOURCE_DIR}/FileLists.cmake )

################################################################################
# build - make
################################################################################
include_directories( ${INC_DIR} ${SRC_DIR} ${PRIV_INC_DIR} ${PRESET_DIR} )

add_library( ${LIB_NAME} SHARED ${SRC_FILES} )
target_link_libraries( ${LIB_NAME} m )

set( TEST_TARGET_LIBRARIES ${LIB_NAME} )

add_testfiles( "${TEST_FILES}" "${TEST_TARGET_LIBRARIES}" )

#add_docfiles( "${DOC_FILES}" )

################################################################################
# install - make install
################################################################################
install( DIRECTORY ${INC_DIR}/clingo DESTINATION /usr/local/include )

install( TARGETS ${LIB_NAME} DESTINATION lib )
