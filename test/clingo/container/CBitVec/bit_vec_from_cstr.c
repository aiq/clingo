#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   char const* bitStr = "00011011 00110011 10101010";
   char const* lowStr = "ooo11o11 oo11oo11 1o1o1o1o";
   char const* invStr = "11100100 11001100 01010101";

   CBitVec* vec = bit_vec_from_cstr_c( bitStr );
   CBitVec* low = bit_vec_from_cstr_c( lowStr );

   expect_at_c_( bit_vec_size_c( vec ) == 24 );
   expect_at_c_( bit_vec_is_c_( vec, bitStr ) );
   expect_at_c_( bit_vec_is_c_( vec, lowStr ) );
   expect_at_c_( eq_bit_vec_c( vec, low ) );
   expect_at_c_( not bit_vec_is_c_( vec, invStr ) );

   release_all_c_( vec, low );

   return finish_tap_c_();
}
