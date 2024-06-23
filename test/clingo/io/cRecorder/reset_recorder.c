#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 12 );

   record_pad_c( rec, '_', 12 );
   reset_recorder_c( rec );

   record_pad_c( rec, ' ', 10 );
   reset_recorder_c( rec );

   record_pad_c( rec, '+', 9 );
   reset_recorder_c( rec );

   record_pad_c( rec, 'X', 7 );
   reset_recorder_c( rec );

   record_pad_c( rec, '+', 5 );
   reset_recorder_c( rec );

   record_pad_c( rec, ' ', 3 );
   reset_recorder_c( rec );

   record_pad_c( rec, '_', 2 );
   move_recorder_c( rec, 10 );

   expect_at_c_( recorded_is_c( rec, "__ ++XX++ __" ) );

   return finish_tap_c_();
}
