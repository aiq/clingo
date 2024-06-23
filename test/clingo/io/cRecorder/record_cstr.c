#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

#define expect_mem_( Slice, ... )                                              \
   expect_eq_c_( cmp_bytes_c_( (Slice), __VA_ARGS__ ) )

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 9 );

   // --------------------------------------------------------------- record abc
   expect_at_c_( record_cstr_c( rec, "abc" ) );
   expect_at_c_( rec->pos == 4 );
   expect_at_c_( rec->space == 5 );

   cBytes recorded = recorded_bytes_c( rec );
   expect_mem_( recorded, 'a', 'b', 'c', '\0' );

   // ------------------------------------------------------ record empty string
   expect_at_c_( record_cstr_c( rec, "" ) );
   expect_at_c_( rec->pos == 5 );
   expect_at_c_( rec->space == 4 );

   recorded = recorded_bytes_c( rec );
   expect_mem_( recorded, 'a', 'b', 'c', '\0', '\0' );

   // ----------------------------------------------- try to record to long cstr
   expect_at_c_( not record_cstr_c( rec, "defg" ) ); // to large
   expect_at_c_( rec->pos == 5 );
   expect_at_c_( rec->space == 4 );

   // --------------------------------------------------------------- record def
   expect_at_c_( record_cstr_c( rec, "def" ) );
   expect_at_c_( rec->pos == 9 );
   expect_at_c_( rec->space == 0 );

   recorded = recorded_bytes_c( rec );
   expect_mem_( recorded, 'a', 'b', 'c', '\0', '\0', 'd', 'e', 'f', '\0' );

   return finish_tap_c_();
}
