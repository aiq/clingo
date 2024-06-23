#include "clingo/container/pile.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

PILE_C_( char, charPile )

static INSERT_C_(
   insert_char, charPile, char, char, do_not_deref_c_, false_realloc_c_
)

#define expect_( Pile, Cstr )                                                  \
   expect_at_c_(                                                                  \
      chars_is_c( as_c_( cChars, (Pile) ), (Cstr) )                            \
   )

int main( void )
{
   init_tap_c_();

   cVarChars slice = slice_c_( char, 'a', 'c', '_', '_', '_' );
   charPile pile = { .s=2, .v=slice.v, .cap=slice.s };
   expect_( pile, "ac" );

   insert_char( &pile, 1, 'b' );
   expect_( pile, "abc" );

   insert_char( &pile, 3, 'd' );
   expect_( pile, "abcd" );

   insert_char( &pile, 0, '>' );
   expect_( pile, ">abcd" );

   return finish_tap_c_();
}