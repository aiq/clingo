#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   CBitVec* vec = new_bit_vec_c( 15 );

   expect_c_( bit_vec_is_c_( vec, "0000 0000 0000 000" ) );

   set_on_bit_vec_c( vec, 0, 1 );
   set_on_bit_vec_c( vec, 3, 1 );
   set_on_bit_vec_c( vec, 4, 1 );
   set_on_bit_vec_c( vec, 7, 1 );
   set_on_bit_vec_c( vec, 10, 1 );
   set_on_bit_vec_c( vec, 11, 1 );
   set_on_bit_vec_c( vec, 14, 1 );

   expect_c_( bit_vec_is_c_( vec, "1001 1001 0011 001" ) );
   
   release_c( vec );

   return finish_tap_c_();
}
