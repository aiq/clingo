
function( add_tests TestFiles IncDirs LinkLibs )
   foreach( TestFile ${TestFiles} )
      get_filename_component( Test ${TestFile} NAME_WE )
      add_executable( ${Test} ${TestFile} )
      target_include_directories( ${Test} PUBLIC ${IncDirs} )
      target_link_libraries( ${Test} PRIVATE ${LinkLibs} )

      add_test( NAME ${Test} COMMAND ${Test} )
   endforeach()
endfunction( add_tests )

