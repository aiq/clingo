#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 128 );

   times_c_( 3, i )
   {
      if ( i < 2 )
      {
         record_chars_c_( rec, "hello, " );
      }
      else
      {
         record_chars_c_( rec, "hello!" );
      }
   }

   expect_at_c_( recorded_is_c( rec, "hello, hello, hello!" ) );

   return finish_tap_c_();
}
