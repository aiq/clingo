#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 10 );
   expect_c_( record_rune_c( rec, rune_c( "🥛" ) ) );
   expect_c_( record_rune_c( rec, rune_c( "🔑" ) ) );
   expect_c_( not record_rune_c( rec, rune_c( "📊" ) ) );

   expect_c_( recorded_is_c( rec, "🥛🔑" ) );

   return finish_tap_c_();
}
