#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "abcdefgh" );
   int64_t idx = 0;

   idx = index_of_chars_c( chars, c_c( "abc" ) ); // ---------------------- abc
   expect_c_( idx == 0 );

   idx = index_of_chars_c_( chars, "cdef" ); // --------------------------- cdef
   expect_c_( idx == 2 );

   idx = index_of_chars_c_( chars, "defgh" ); // ------------------------- defgh
   expect_c_( idx == 3 );

   idx = index_of_chars_c_( chars, "h" ); // --------------------------------- h
   expect_c_( idx == 7 );

   idx = index_of_chars_c_( chars, "BCD" ); // ----------------------------- BCD
   expect_c_( idx == -1 );

   idx = index_of_chars_c_( chars, "ghij" ); // --------------------------- ghij
   expect_c_( idx == -1 );

   return finish_tap_c_();
}
