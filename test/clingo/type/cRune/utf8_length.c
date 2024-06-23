#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   char const* cs1 = "y";
   expect_at_c_( utf8_length_c( cs1[0] ) == 1 );

   char const* cs2 = "®";
   expect_at_c_( utf8_length_c( cs2[0] ) == 2 );

   char const* cs3 = "€";
   expect_at_c_( utf8_length_c( cs3[0] ) == 3 );

   char const* cs4 = "𝄞";
   expect_at_c_( utf8_length_c( cs4[0] ) == 4 );

   expect_at_c_( utf8_length_c( char_c_( 0xff ) ) == 0 );

   return finish_tap_c_();
}
