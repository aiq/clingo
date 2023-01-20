#include "clingo/lang/expect.h"
#include "clingo/type/cCharsSlice.h"

#define expect_( Res, Exp )                                                    \
   expect_c_( chars_is_c( (Res), (Exp) ) )

int main( void )
{
   init_tap_c_();

   cVarChars buf = var_chars_c_( 128 );
   cCharsSlice slice = cs_c_( "abc", "def", "gh", "ij", "klmn", "opq" );

   expect_( join_chars_slice_c_( slice, "", buf ),
            "abcdefghijklmnopq" );
   expect_( join_chars_slice_c_( slice, "-", buf ),
            "abc-def-gh-ij-klmn-opq" );
   expect_( join_chars_slice_c_( slice, " - ", buf ),
            "abc - def - gh - ij - klmn - opq" );

   return finish_tap_c_();
}
