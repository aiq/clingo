#include "clingo/lang/expect.h"
#include "clingo/type/cCharsSlice.h"

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "abcdefgh" );
   int64_t idx = 0;

   idx = index_of_any_chars_c_( chars, "def", "fgh", "abc" ); // ----------- abc
   expect_c_( idx == 0 );

   idx = index_of_any_chars_c_( chars, "def", "fgh" ); // ------------------ def
   expect_c_( idx == 3 );

   idx = index_of_any_chars_c_( chars, "fght", "adcg" ); // --------------------
   expect_c_( idx == -1 );

   return finish_tap_c_();
}