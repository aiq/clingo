#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h" // remove_char_c

#define expect_( VarSlice, Cstr )                                              \
   expect_at_c_(                                                                  \
      chars_is_c( as_c_( cChars, (VarSlice) ), (Cstr) )                        \
   )

int main( void )
{
   init_tap_c_();

   cVarChars slice = slice_c_( char, 'a', 'b', 'c', 'd', 'e' );
   expect_( slice, "abcde" );

   remove_char_c( &slice, 2 );
   expect_( slice, "abde" );

   remove_char_c( &slice, 0 );
   expect_( slice, "bde" );

   remove_char_c( &slice, 2 );
   expect_( slice, "bd" );

   return finish_tap_c_();
}