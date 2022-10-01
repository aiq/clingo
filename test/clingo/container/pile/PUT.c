#include "clingo/container/pile.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

PILE_C_( char, charPile )

static PUT_C_(
   put_char, charPile, char, do_not_deref_c_, false_realloc_c_
)

#define expect_( Pile, Cstr )                                                  \
   expect_c_(                                                                  \
      chars_is_c( as_c_( cChars, (Pile) ), (Cstr) )                            \
   )

int main( void )
{
   init_tap_c_();

   cVarChars slice = slice_c_( char, 'a', '_', '_', '_' );
   charPile pile = { .s=1, .v=slice.v, .cap=slice.s };
   expect_( pile, "a" );

   put_char( &pile, 'b' );
   expect_( pile, "ab" );

   put_char( &pile, 'c' );
   expect_( pile, "abc" );

   put_char( &pile, 'd' );
   expect_( pile, "abcd" );

   return finish_tap_c_();
}