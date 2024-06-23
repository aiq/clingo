#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/float.h" // swap_float_to_c

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 13 );

   float const val = 123.456f;

   // -------------------------------- value is written in the system byte order
   float const* recVal = rec->mem;
   expect_at_c_( record_float_c( rec, val ), 4 );
   expect_at_c_( rec->pos == 4 );
   expect_at_c_( rec->space == 9 );
   expect_at_c_( *recVal == val );

   // ----------------------------------------- write with a specific byte order
   float const bigVal = swap_float_to_c( val, c_BigEndian );
   float const littleVal = swap_float_to_c( val, c_LittleEndian );

   float const* recBig = rec->mem;
   expect_at_c_( record_float_c( rec, bigVal ) );
   float const* recLittle = rec->mem;
   expect_at_c_( record_float_c( rec, littleVal ) );

   expect_at_c_( *recBig != *recLittle );

   // --------------------------------------- try to record without enough space
   expect_at_c_( not record_float_c( rec, 4.5f ) );
   expect_at_c_( rec->pos == 12 );
   expect_at_c_( rec->space == 1 );

   return finish_tap_c_();
}
