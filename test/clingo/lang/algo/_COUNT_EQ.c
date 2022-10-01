#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h" // count_eq_char_c

int main( void )
{
   init_tap_c_();

   cChars cheese = c_c( "cheese" );
   expect_c_( count_eq_char_c( cheese, 'e' ) == 3 );
   expect_c_( count_eq_char_c( cheese, 'x' ) == 0 );

   cChars text = c_c( "The quick brown Fox jumps over the lazy Dog." );
   expect_c_( count_eq_char_c( text, ' ' ) == 8 );
   expect_c_( count_eq_char_c( text, 'o' ) == 4 );
   expect_c_( count_eq_char_c( text, 'T' ) == 1 );
   expect_c_( count_eq_char_c( text, 't' ) == 1 );

   return finish_tap_c_();
}
