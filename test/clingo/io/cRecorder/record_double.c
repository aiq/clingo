#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/double.h" // swap_double_to_c

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 27 );

   double const val = 209348.034;

   // -------------------------------- value is written in the system byte order
   double const* recVal = rec->mem;
   expect_true_c_( record_double_c( rec, val ) );
   expect_equal_c_( rec->pos, 8 );
   expect_equal_c_( rec->space, 19 );
   expect_equal_c_( *recVal, val );

   // ----------------------------------------- write with a specific byte order
   double const bigVal = swap_double_to_c( val, c_BigEndian );
   double const littleVal = swap_double_to_c( val, c_LittleEndian );

   double const* recBig = rec->mem;
   expect_true_c_( record_double_c( rec, bigVal ) );
   double const* recLittle = rec->mem;
   expect_true_c_( record_double_c( rec, littleVal ) );

   expect_not_equal_c_( *recBig, *recLittle );

   // --------------------------------------- try to record without enough space
   expect_false_c_( record_double_c( rec, 1.4 ) );
   expect_equal_c_( rec->pos, 24 );
   expect_equal_c_( rec->space, 3 );

   return finish_tap_c_();
}
