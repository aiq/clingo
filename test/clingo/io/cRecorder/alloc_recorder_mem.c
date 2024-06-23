#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &null_recorder_c_();

   expect_at_c_( alloc_recorder_mem_c( rec, 5 ) );
   expect_at_c_( rec->pos == 0 );
   expect_at_c_( rec->space == 5 );
   expect_at_c_( rec->mem != NULL );
   expect_at_c_( rec->dyn == false );

   expect_at_c_( not record_chars_c_( rec, "abcdef" ) ); // to large

   expect_at_c_( record_chars_c_( rec, "abcde" ) );

   free_recorder_mem_c( rec );

   return finish_tap_c_();
}
