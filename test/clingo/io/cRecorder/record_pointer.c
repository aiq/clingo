#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 128 );

   char const* ptr1 = "first";
   record_pointer_c( rec, ptr1 );

   void* ptr2 = NULL;
   record_pointer_c( rec, ptr2 );

   uint8_t const* ptr3 = ref_c_( uint8_t, 23 );
   record_pointer_c( rec, ptr3 );

   cBytes buf = recorded_bytes_c( rec );
   cScanner* sca = &make_scanner_c_( buf.s, buf.v );

   char const* res1 = NULL;
   scan_pointer_c_( sca, &res1 );
   expect_at_c_( ptr1 == res1 );
   expect_at_c_( cstr_is_c( res1, "first" ) );

   void* res2 = NULL;
   scan_pointer_c_( sca, &res2 );
   expect_at_c_( ptr2 == res2 );

   uint8_t const* res3 = NULL;
   scan_pointer_c_( sca, &res3 );
   expect_at_c_( ptr3 == res3 );
   expect_at_c_( *res3 == 23 );

   expect_at_c_( sca->space == 0 );

   return finish_tap_c_();
}
