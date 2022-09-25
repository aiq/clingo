#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

#define expect_( VarChars, Exp )                                               \
   expect_c_(                                                                  \
      chars_is_c( as_c_( cChars, VarChars ), (Exp) )                           \
   )

int main( void )
{
   init_tap_c_();

   cVarChars chars = slice_c_( char, 'a', 'B', 'c', 'D', 'e', 'F' );

   // rotate left and right
   rotate_chars_c( chars, -2 );
   expect_( chars, "cDeFaB" );

   rotate_chars_c( chars, 2 );
   expect_( chars, "aBcDeF" );

   // handle full rotations correct
   rotate_chars_c( chars, 0 );
   expect_( chars, "aBcDeF" );

   rotate_chars_c( chars, 6 );
   expect_( chars, "aBcDeF" );

   // handle multiple time rotations right
   rotate_chars_c( chars, 9 );
   expect_( chars, "DeFaBc" );

   rotate_chars_c( chars, -27 );
   expect_( chars, "aBcDeF" );

   return finish_tap_c_();
}
