#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   CBitVec* vec = bit_vec_from_cstr_c( "00100010" );

   expect_at_c_( find_index_of_bit_c( vec, 1, 0 ) == 2 );
   expect_at_c_( find_index_of_bit_c( vec, 0, 3 ) == 3 );
   expect_at_c_( find_index_of_bit_c( vec, 1, 3 ) == 6 );

   release_c( vec );

   return finish_tap_c_();
}
