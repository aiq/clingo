#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 2 );

   // ------------------------------------------------------ write int8_t values
   int8_t const* plusVal = rec->mem;
   expect_at_c_( record_int8_c( rec, 127 ) );
   expect_at_c_( rec->pos == 1 );
   expect_at_c_( rec->space == 1 );
   expect_at_c_( *plusVal == 127 );

   int8_t const* minusVal = rec->mem;
   expect_at_c_( record_int8_c( rec, -128 ) );
   expect_at_c_( rec->pos == 2 );
   expect_at_c_( rec->space == 0 );
   expect_at_c_( *minusVal == -128 );

   // --------------------------------------- try to record without enough space
   expect_at_c_( not record_int8_c( rec, 32 ) );
   expect_at_c_( rec->pos == 2 );
   expect_at_c_( rec->space == 0 );

   return finish_tap_c_();
}
