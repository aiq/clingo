#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 2 );

   // ------------------------------------------------- ---- write int8_t values
   uint8_t const* val128 = rec->mem;
   expect_at_c_( record_uint8_c( rec, 128 ) );
   expect_at_c_( rec->pos == 1 );
   expect_at_c_( rec->space == 1 );
   expect_at_c_( *val128 == 128 );

   uint8_t const* val255 = rec->mem;
   expect_at_c_( record_uint8_c( rec, 255 ) );
   expect_at_c_( rec->pos == 2 );
   expect_at_c_( rec->space == 0 );
   expect_at_c_( *val255 == 255 );

   // --------------------------------------- try to record without enough space
   expect_at_c_( not record_uint8_c( rec, 32 ) );
   expect_at_c_( rec->pos == 2 );
   expect_at_c_( rec->space == 0 );

   return finish_tap_c_();
}
