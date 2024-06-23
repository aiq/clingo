#include "clingo/lang/expect.h"
#include "clingo/type/char.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( hex_char_value_c( '0' ) ==  0 );
   expect_at_c_( hex_char_value_c( 'F' ) == 15 );
   expect_at_c_( hex_char_value_c( 'f' ) == 15 );
   expect_at_c_( hex_char_value_c( 'x' ) == -1 );
   expect_at_c_( hex_char_value_c( 'g' ) == -1 );

   return finish_tap_c_();
}
