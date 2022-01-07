#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   CBitVec* vec = bit_vec_from_cstr_c( "0101" );

   compl_on_bit_vec_c( vec );
   expect_c_( bit_vec_is_c_( vec, "1010" ) );

   release_all_c_( vec );

   return finish_tap_c_();
}
