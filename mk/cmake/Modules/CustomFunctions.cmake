
function( add_testfiles TESTFILES TARGET_LIBRARIES )
   foreach( TESTFILE ${TESTFILES} )
      get_filename_component( TEST ${TESTFILE} NAME_WE )
      add_executable( ${TEST} ${TESTFILE} )
      target_link_libraries( ${TEST} ${TARGET_LIBRARIES} m )

      add_test( NAME ${TEST} COMMAND ${TEST} )
   endforeach()
endfunction( add_testfiles )

