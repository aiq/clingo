#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "® yes this is a 𝄞 and €!" );
   cRune r;
   char const* itr;

   itr = next_rune_c( chars, NULL, &r );
   expect_c_( rune_is_c( r, "®" ) );

   itr = next_rune_c( chars, itr, &r );
   expect_c_( rune_is_c( r, " " ) );
   expect_eq_c_( strcmp( " yes this is a 𝄞 and €!", itr ) );

   itr = next_rune_c( chars, itr, &r );
   expect_c_( rune_is_c( r, "y" ) );
   expect_eq_c_( strcmp( "yes this is a 𝄞 and €!", itr ) );

   return finish_tap_c_();
}
