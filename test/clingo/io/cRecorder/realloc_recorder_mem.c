#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &null_recorder_c_();

   expect_c_( alloc_recorder_mem_c( rec, 3 ) );
   expect_c_( record_chars_c_( rec, "ab" ) );
   expect_c_( not record_chars_c_( rec, "cdef" ) ); // to large


   expect_c_( realloc_recorder_mem_c( rec, 6 ) );
   expect_c_( rec->pos == 2 );
   expect_c_( rec->space == 4 );
   expect_c_( rec->mem != NULL );

   expect_c_( record_chars_c_( rec, "cdef" ) );

   free_recorder_mem_c( rec );

   return finish_tap_c_();
}
