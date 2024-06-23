#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   CBitVec* orig = bit_vec_from_cstr_c( "01011010" );
   CBitVec* copy = copy_bit_vec_c( orig );

   expect_at_c_( orig != copy );
   expect_at_c_( bit_vec_is_c_( copy, "01011010" ) );

   release_all_c_( orig, copy );

   return finish_tap_c_();
}
