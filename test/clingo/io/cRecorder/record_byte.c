#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

#define expect_mem_( Slice, ... )                                              \
   expect_eq_c_( cmp_bytes_c_( (Slice), __VA_ARGS__ ) )

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------ init recorder
   cRecorder* rec = &recorder_c_( 6 );
   expect_at_c_( rec->pos == 0 );
   expect_at_c_( rec->space == 6 );
   expect_at_c_( is_empty_c_( recorded_bytes_c( rec ) ) );

   // ----------------------------------------------------------- record 3 bytes
   expect_at_c_( record_byte_c( rec, 0xab ) );
   expect_at_c_( record_byte_c( rec, 0xcd ) );
   expect_at_c_( record_byte_c( rec, 0xef ) );

   expect_at_c_( rec->pos == 3 );
   expect_at_c_( rec->space == 3 );

   cBytes recorded = recorded_bytes_c( rec );
   expect_at_c_( recorded.s == 3 );
   expect_mem_( recorded, 0xab, 0xcd, 0xef );

   // --------------------------------------------------------------- fill space
   while ( record_byte_c( rec, 0xcc ) ){}

   recorded = recorded_bytes_c( rec );
   expect_at_c_( recorded.s == 6 );
   expect_mem_( recorded, 0xab, 0xcd, 0xef, 0xcc, 0xcc, 0xcc );

   return finish_tap_c_();
}
