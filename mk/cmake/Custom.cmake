################################################################################
# custom cmake changes
################################################################################

set( CMAKE_COLOR_MAKEFILE ON )

set( CUSTOM_FLAGS_LIST
   -Wall
   -Wabsolute-value
   -Werror=absolute-value
   -Waddress-of-temporary
   -Werror=address-of-temporary
   -Wconversion # Warn for implicit conversions that may alter a value.
   -Werror=conversion
   -Wunused-function
   -Werror=unused-function
)
list( JOIN CUSTOM_FLAGS_LIST " " CUSTOM_FLAGS )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUSTOM_FLAGS}" )

################################################################################
# custom functions
################################################################################

function( add_tests TestFiles IncDirs LinkLibs )
   foreach( TestFile IN LISTS TestFiles )
      get_filename_component( Test ${TestFile} NAME_WE )
      add_executable( ${Test} ${TestFile} )
      target_include_directories( ${Test} PUBLIC ${IncDirs} )
      target_link_libraries( ${Test} PRIVATE ${LinkLibs} )

      add_test( NAME ${Test} COMMAND ${Test} )
   endforeach()
endfunction( add_tests )
