#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 100 );

   // --------------------------------------------------------------- first step
   {
      expect_c_( recordf_c( rec, "%s\nThe half of %d is %d.", "Example:",
                                                              60,
                                                              60/2 ) );
      expect_c_( recorded_is_c( rec, "Example:\n"
                                     "The half of 60 is 30." ) );
   }

   // -------------------------------------------------------------- second step
   {
      move_recorder_c( rec, -1 ); // to remove the dot
      expect_c_( recordf_c( rec, ", and the half of that is %d.", 60/2/2 ) );
      char const* txt = "Example:\n"
                        "The half of 60 is 30, and the half of that is 15.";
      expect_c_( recorded_is_c( rec, txt ) );
   }

   return finish_tap_c_();
}
