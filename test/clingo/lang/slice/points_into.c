#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abc = c_c( "abc" );

   expect_c_(  points_into_c_( abc, begin_c_( abc ) ) );
   expect_c_(  points_into_c_( abc, rbegin_c_( abc ) ) );
   expect_c_( !points_into_c_( abc, end_c_( abc ) ) );
   expect_c_( !points_into_c_( abc, rend_c_( abc ) ) );

   char const* ptr = begin_c_( abc );
   ptr++;
   expect_c_( points_into_c_( abc, ptr ) );

   ptr = NULL;
   expect_c_( !points_into_c_( abc, ptr ) );

   return finish_tap_c_();
}
