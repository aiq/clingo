#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"

int main( void )
{
   init_tap_c_();

   int64_t foobar = 42;
   expect_c_( concat3_c_( fo, ob, ar ) == 42 );

   return finish_tap_c_();
}
