#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   // ®=2 / 𝄞=4 / €=3
   cChars chars1 = c_c( "® yes this is a 𝄞 and €!" );
   expect_c_( chars1.s == 30 );
   expect_c_( count_runes_c( chars1 ) == 24 );

   cChars chars2 = c_c( "abcdefgh" );
   expect_c_( chars2.s == 8 );
   expect_c_( count_runes_c( chars2 ) == 8 );

   cChars empty = empty_chars_c();
   expect_c_( count_runes_c( empty ) == 0 );

   cChars euroSign = chars_c( 7, "euro:€" ); // wrong size
   expect_c_( count_runes_c( euroSign ) == -1 );
   euroSign.s = 8;
   expect_c_( count_runes_c( euroSign ) == 6 );

   return finish_tap_c_();
}
