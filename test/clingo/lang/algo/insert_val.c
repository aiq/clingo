#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

#define expect_( VarChars, Exp )                                               \
   expect_c_(                                                                  \
      chars_is_c( as_chars_c( VarChars ), (Exp) )                              \
   )

int main( void )
{
   init_tap_c_();

   cVarChars allChars = scalars_c_( 8, char );
   set_chars_c_( allChars, "#abcdef#" );

   cVarChars subChars = sub_var_chars_c( allChars, 1, 7 );

   // ----------------------------------------------------- insert in the middle
   expect_c_( insert_char_c( subChars, 1, '+' ) == 1 );
   expect_( allChars, "#a+bcde#" );

   expect_c_( insert_char_c( subChars, 3, '-' ) == 1 );
   expect_( allChars, "#a+b-cd#" );

   // ---------------------------------------------------- insert at the corners
   expect_c_( insert_char_c( subChars, 0, '$' ) == 1 );
   expect_( allChars, "#$a+b-c#" );

   expect_c_( insert_char_c( subChars, 5, 'X' ) == 1 );
   expect_( allChars, "#$a+b-X#" );

   // ---------------------------------------------------- try to insert outside
   expect_c_( insert_char_c( subChars, -1, '_' ) == 0 );
   expect_( allChars, "#$a+b-X#" );

   expect_c_( insert_char_c( subChars, 6, '_' ) == 0 );
   expect_( allChars, "#$a+b-X#" );

   return finish_tap_c_();
}
