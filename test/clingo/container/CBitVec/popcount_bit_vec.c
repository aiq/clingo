#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   {
      CBitVec* vec = bit_vec_from_cstr_c( "00111111" );

      expect_c_( popcount_bit_vec_c( vec, 0 ) == 2 );
      expect_c_( popcount_bit_vec_c( vec, 1 ) == 6 );

      release_c( vec );
   }
   {
      CBitVec* vec = bit_vec_from_cstr_c( "00001111 11000000 1001" );

      expect_c_( popcount_bit_vec_c( vec, 0 ) == 12 );
      expect_c_( popcount_bit_vec_c( vec, 1 ) ==  8 );

      release_c( vec );
   }

   return finish_tap_c_();
}
