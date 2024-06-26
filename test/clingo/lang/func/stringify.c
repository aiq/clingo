#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"
#include "clingo/type/cChars.h"

#define expect_( Str, Exp )                                                    \
   expect_at_c_( chars_is_c( c_c( Str ), (Exp) ) )

int main( void )
{
   init_tap_c_();

   #define x 2
   char const* str = stringify_c_( x + 2 );
   expect_( str, "x + 2" );

   return finish_tap_c_();
}
