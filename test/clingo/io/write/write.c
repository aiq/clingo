#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "clingo/time/cDuration.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 1024 );

   expect_at_c_( write_c_( rec,
      "{i64:q} is more as {i64:Q} ", imax64_c( 64, 3 ), imin64_c( 64, 3 ),
      "but both are in range {rng:c}{s}\n", closed_range_c_( 0, 64 ), "BOOM!",
      "{{really}\n", "BOOM!\n",
      "{cs:q}\n", c_c( "_" ),
      "that is so {bool}\n", true,
      "and took {:hhmmss}", duration_tape_c_( duration_c( 3, 59, 47, 0 ) )
   ) );
   expect_at_c_( recorded_is_c( rec,
      "'64' is more as \"3\" but both are in range [0..64]BOOM!\n"
      "{really}\n"
      "BOOM!\n"
      "'_'\n"
      "that is so true\n"
      "and took 3h59m47s" ) );

   reset_recorder_c( rec );
   expect_at_c_( write_c_( rec, "res = {bool}", true ) );
   expect_at_c_( recorded_is_c( rec, "res = true" ) );

   return finish_tap_c_();
}
