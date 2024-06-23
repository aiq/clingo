#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   CBitVec* vec = bit_vec_from_cstr_c( "0101" );

   CBitVec* res = compl_bit_vec_c( vec );
   expect_at_c_( bit_vec_is_c_( res, "1010" ) );

   release_all_c_( vec, res );

   return finish_tap_c_();
}
