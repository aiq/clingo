#include "clingo/lang/expect.h"
#include "clingo/type/char.h"

int main( void )
{
   init_tap_c_();

   expect_c_( dec_char_value_c( '0' ) ==  0 );
   expect_c_( dec_char_value_c( '5' ) ==  5 );
   expect_c_( dec_char_value_c( '9' ) ==  9 );
   expect_c_( dec_char_value_c( 'x' ) == -1 );
   expect_c_( dec_char_value_c( 'A' ) == -1 );

   return finish_tap_c_();
}
