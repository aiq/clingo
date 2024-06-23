#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"

int main( void )
{
   init_tap_c_();

   int64_t count = 0;
   once_c_( xyz )
   {
      ++count;
   }

   expect_at_c_( count == 1 );

   return finish_tap_c_();
}
