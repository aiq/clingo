#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

#define expect_( VarChars, Exp )                                               \
   expect_c_(                                                                  \
      chars_is_c( as_chars_c( VarChars ), (Exp) )                              \
   )

int main( void )
{
   init_tap_c_();

   cVarChars allChars = scalars_c_( 14, char );
   set_chars_c_( allChars, "#abcdefghijkl#" );

   cVarChars subChars = sub_var_chars_c( allChars, 1, 13 );

   // ----------------------------------------------------- insert in the middle
   expect_c_( insert_chars_c( subChars, 1, c_c( "AA" ) ) == 2 );
   expect_( allChars, "#aAAbcdefghij#" );

   expect_c_( insert_chars_c_( subChars, 4, "BBB" ) == 3 );
   expect_( allChars, "#aAAbBBBcdefg#" );

   expect_c_( insert_chars_c_( subChars, 8, "CCCC" ) == 4 );
   expect_( allChars, "#aAAbBBBcCCCC#" );

   // ---------------------------------------------------- insert at the corners
   expect_c_( insert_chars_c_( subChars, 0, "_" ) == 1 );
   expect_( allChars, "#_aAAbBBBcCCC#" );

   expect_c_( insert_chars_c_( subChars, 10, "d___" ) == 2 );
   expect_( allChars, "#_aAAbBBBcCd_#" );

   // ---------------------------------------------------- try to insert outside
   expect_c_( insert_chars_c_( subChars, -1, "xxx" ) == 0 );
   expect_( allChars, "#_aAAbBBBcCd_#" );

   expect_c_( insert_chars_c_( subChars, 12, "xxx" ) == 0 );
   expect_( allChars, "#_aAAbBBBcCd_#" );

   return finish_tap_c_();
}
