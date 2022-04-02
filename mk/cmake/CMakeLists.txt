cmake_minimum_required( VERSION 3.2 )

project( clingo VERSION 0.1.0 LANGUAGES C )
set( CMAKE_C_STANDARD          11 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_EXTENSIONS        OFF )

enable_testing()

set( LIB_NAME ${PROJECT_NAME} )

# where to look first for modules, before ${CMAKE_ROOT}/Modules/ is checked
set( ROOT ${CMAKE_SOURCE_DIR}/../.. )
set( DOC_DIR ${ROOR}/doc )
set( INC_DIR ${ROOT}/inc )
set( SRC_DIR ${ROOT}/src )
set( TEST_DIR ${ROOT}/test )

include( CTest )
include( ${CMAKE_SOURCE_DIR}/Custom.cmake )
include( ${CMAKE_SOURCE_DIR}/FileLists.cmake )

################################################################################
# build - make
################################################################################
add_library( ${LIB_NAME} SHARED ${SRC_FILES} )
target_include_directories( ${LIB_NAME} PUBLIC ${INC_DIR} PRIVATE ${SRC_DIR} )
target_link_libraries( ${LIB_NAME} PUBLIC m )

set( TEST_INC_DIRS ${INC_DIR} ${SRC_DIR} )
set( TEST_LINK_LIBS ${LIB_NAME} m )
add_tests( "${TEST_FILES}" "${TEST_INC_DIRS}" "${TEST_LINK_LIBS}" )

#add_docfiles( "${DOC_FILES}" )

################################################################################
# install - make install
################################################################################
install( DIRECTORY ${INC_DIR}/clingo DESTINATION /usr/local/include )

install( TARGETS ${LIB_NAME} DESTINATION lib )
