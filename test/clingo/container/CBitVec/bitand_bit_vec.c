#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   CBitVec* a = bit_vec_from_cstr_c( "0101" );
   CBitVec* b = bit_vec_from_cstr_c( "0011" );

   CBitVec* res = bitand_bit_vec_c( a, b );
   expect_c_( bit_vec_is_c_( res, "0001" ) );

   release_all_c_( a, b, res );

   return finish_tap_c_();
}
