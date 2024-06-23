#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   char const* cs1 = "®"; // size 2
   expect_at_c_( !is_utf8_tail_c( cs1[0] ) );
   expect_at_c_(  is_utf8_tail_c( cs1[1] ) );

   char const* cs2 = "€"; // size 3
   expect_at_c_( !is_utf8_tail_c( cs2[0] ) );
   expect_at_c_(  is_utf8_tail_c( cs2[1] ) );
   expect_at_c_(  is_utf8_tail_c( cs2[2] ) );

   char const* cs3 = "𝄞"; // size 4
   expect_at_c_( !is_utf8_tail_c( cs3[0] ) );
   expect_at_c_(  is_utf8_tail_c( cs3[1] ) );
   expect_at_c_(  is_utf8_tail_c( cs3[2] ) );
   expect_at_c_(  is_utf8_tail_c( cs3[3] ) );

   return finish_tap_c_();
}
