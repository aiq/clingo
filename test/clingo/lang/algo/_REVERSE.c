#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h" // reverse_chars_c

#define expect_( VarChars, Exp )                                               \
   expect_c_(                                                                  \
      chars_is_c( as_c_( cChars, VarChars ), (Exp) )                           \
   )

int main( void )
{
   init_tap_c_();

   cVarChars a = slice_c_( char, 'a' );
   reverse_chars_c( a );
   expect_( a, "a" );

   cVarChars ab = slice_c_( char, 'a', 'b' );
   reverse_chars_c( ab );
   expect_( ab, "ba" );

   cVarChars abc = slice_c_( char, 'a', 'b', 'c' );
   reverse_chars_c( abc );
   expect_( abc, "cba" );

   cVarChars abcd = slice_c_( char, 'a', 'b', 'c', 'd' );
   reverse_chars_c( abcd );
   expect_( abcd, "dcba" );

   return finish_tap_c_();
}
