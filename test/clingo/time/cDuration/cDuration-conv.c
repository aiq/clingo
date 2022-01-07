#include "clingo/lang/expect.h"
#include "clingo/time/cDuration.h"

int main( void )
{
   init_tap_c_();

   // 32 mins == 1920 secs
   cDuration shortDur = duration_c( 0, 32, 15, 123456789 );
   expect_c_( as_mins_c( shortDur )  == 32 );
   expect_c_( as_secs_c( shortDur )  == 1935 );
   expect_c_( as_msecs_c( shortDur ) == 1935123L );
   expect_c_( as_usecs_c( shortDur ) == 1935123456L );
   expect_c_( as_nsecs_c( shortDur ) == 1935123456789L );

   return finish_tap_c_();
}
