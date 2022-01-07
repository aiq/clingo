#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   // ®=2 / 𝄞=4 / €=3
   cChars chars = c_c( "® yes 𝄞 and €!" );

   char const* res = find_rune_c( chars, rune_c( "𝄞" ) );
   expect_c_( index_of_c_( chars, res ) == 7 );
   expect_c_( rune_is_c( rune_c( res ), "𝄞" ) );

   res = find_rune_c_( chars, "€" );
   expect_c_( index_of_c_( chars, res ) == 16 );
   expect_c_( rune_is_c( rune_c( res ), "€" ) );

   res = find_rune_c_( chars, "x" );
   expect_c_( index_of_c_( chars, res ) == -1 );
   expect_c_( res == NULL );

   chars.s = 17; // ends in the middle of '€'
   res = find_rune_c_( chars, "€" );
   expect_c_( index_of_c_( chars, res ) == -1 );
   expect_c_( res == NULL );

   return finish_tap_c_();
}
