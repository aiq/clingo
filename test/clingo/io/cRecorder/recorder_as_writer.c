#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

#define expect_mem_( Slice, ... )                                              \
   expect_eq_c_( cmp_bytes_c_( (Slice), __VA_ARGS__ ) )

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 256 );

   cWriter w = recorder_as_writer_c( rec );

   bool res = do_write_c_( w, "this is {i64} large text about {s:q}", 1, "nothing" );

   expect_c_( res );
   expect_c_( recorded_is_c( rec, "this is 1 large text about 'nothing'" ) );

   return finish_tap_c_();
}
