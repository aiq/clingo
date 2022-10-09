#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h" // take_char_c

#define expect_( VarSlice, Cstr )                                              \
   expect_c_(                                                                  \
      chars_is_c( as_c_( cChars, (VarSlice) ), (Cstr) )                        \
   )

int main( void )
{
   init_tap_c_();

   cVarChars slice = slice_c_( char, '+', 'a', 'b', '-', 'c', 'x' );
   expect_( slice, "+ab-cx" );

   char val;
   take_char_c( &slice, 5, &val );
   expect_( slice, "+ab-c" );
   expect_c_( val == 'x' );

   take_char_c( &slice, 0, &val );
   expect_( slice, "ab-c" );
   expect_c_( val == '+' );

   take_char_c( &slice, 2, &val );
   expect_( slice, "abc" );
   expect_c_( val == '-' );

   return finish_tap_c_();
}