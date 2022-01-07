#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abc = c_c( "abc" );

   char const* ptr = NULL;
   expect_c_( index_of_c_( abc, ptr ) == -1 );

   ptr = begin_c_( abc );
   expect_c_( index_of_c_( abc, ptr ) == 0 );

   ptr++;
   expect_c_( index_of_c_( abc, ptr ) == 1 );

   ptr = rbegin_c_( abc );
   expect_c_( index_of_c_( abc, ptr ) == 2 );

   ptr = end_c_( abc );
   expect_c_( index_of_c_( abc, ptr ) == -1 );

   ptr = rend_c_( abc );
   expect_c_( index_of_c_( abc, ptr ) == -1 );

   return finish_tap_c_();
}
