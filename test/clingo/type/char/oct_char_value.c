#include "clingo/lang/expect.h"
#include "clingo/type/char.h"

int main( void )
{
   init_tap_c_();

   expect_c_( oct_char_value_c( '0' ) ==  0 );
   expect_c_( oct_char_value_c( '4' ) ==  4 );
   expect_c_( oct_char_value_c( '7' ) ==  7 );
   expect_c_( oct_char_value_c( '8' ) == -1 );
   expect_c_( oct_char_value_c( '!' ) == -1 );

   return finish_tap_c_();
}
