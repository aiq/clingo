#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars base = c_c( "- This, string." );
   cChars chars = base;
   cChars set = c_c( " ,.-" );

   char const* ptr = NULL;
   int64_t idx = -1;

   ptr = find_any_char_c( chars, set ); // --------------------------------- '-'
   idx = index_of_c_( base, ptr );
   expect_c_( *ptr == '-' );
   expect_c_( idx == 0 );
   chars = mid_chars_c( base, idx+1 );

   ptr = find_any_char_c( chars, set ); // --------------------------------- ' '
   idx = index_of_c_( base, ptr );
   expect_c_( *ptr == ' ' );
   expect_c_( idx == 1 );
   chars = mid_chars_c( base, idx+1 );

   ptr = find_any_char_c( chars, set ); // --------------------------------- ','
   idx = index_of_c_( base, ptr );
   expect_c_( *ptr == ',' );
   expect_c_( idx == 6 );
   chars = mid_chars_c( base, idx+1 );

   ptr = find_any_char_c( chars, set ); // --------------------------------- ' '
   idx = index_of_c_( base, ptr );
   expect_c_( *ptr == ' ' );
   expect_c_( idx == 7 );
   chars = mid_chars_c( base, idx+1 );

   ptr = find_any_char_c( chars, set ); // --------------------------------- '.'
   idx = index_of_c_( base, ptr );
   expect_c_( *ptr == '.' );
   expect_c_( idx == 14 );
   chars = mid_chars_c( base, idx+1 );

   return finish_tap_c_();
}
