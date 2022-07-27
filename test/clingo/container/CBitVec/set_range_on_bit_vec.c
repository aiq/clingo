#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   CBitVec* vec = bit_vec_from_cstr_c( "1000 0001 0000 001" );

   set_range_on_bit_vec_c( vec, closed_range_c_( 5, 9 ), 1 );
   expect_c_( bit_vec_is_c_( vec, "1000 0111 1100 001" ) );

   set_range_on_bit_vec_c( vec, closed_range_c_( 6, 8 ), 0 );
   expect_c_( bit_vec_is_c_( vec, "1000 0100 0100 001" ) );

   set_range_on_bit_vec_c( vec, closed_range_c_( 17, 19 ), 1 );
   expect_c_( bit_vec_is_c_( vec, "1000 0100 0100 0010 0111" ) );

   set_range_on_bit_vec_c( vec, closed_range_c_( 18, 25 ), 0 );
   expect_c_( bit_vec_is_c_( vec, "1000 0100 0100 0010 0100" ) );

   release_c( vec );

   return finish_tap_c_();
}
