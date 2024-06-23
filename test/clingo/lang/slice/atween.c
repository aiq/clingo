#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars cs = c_c( "abcdef" );

   char const* beg = begin_c_( cs );
   char const* end = end_c_( cs );

   cChars abcdef = atween_c_( beg, end );
   expect_at_c_( chars_is_c( abcdef, "abcdef" ) );

   ++beg;
   --end;
   cChars bcde = atween_c_( beg, end );
   expect_at_c_( chars_is_c( bcde, "bcde" ) );

   return finish_tap_c_();
}
