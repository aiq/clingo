################################################################################
# custom cmake changes
################################################################################

set( CMAKE_COLOR_MAKEFILE ON )

function( set_default_flags TargetName )
   target_compile_options( ${TargetName} PRIVATE
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
endfunction( set_default_flags )

################################################################################
# custom functions
################################################################################

function( add_tests Project TestFiles IncDirs LinkLibs )
   foreach( TestFile IN LISTS TestFiles )
      get_filename_component( Test ${TestFile} NAME_WE )
      add_executable( "${Project}-${Test}"  ${TestFile} )
      target_include_directories( "${Project}-${Test}" PUBLIC ${IncDirs} )
      target_link_libraries( "${Project}-${Test}" PRIVATE ${LinkLibs} )

      add_test( NAME "${Project}-${Test}" COMMAND "${Project}-${Test}" )
   endforeach()
endfunction( add_tests )
