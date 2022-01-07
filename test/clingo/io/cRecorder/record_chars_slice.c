#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cCharsSlice.h"

#define expect_( Rec, Exp )                                                    \
   expect_c_( recorded_is_c( (Rec), (Exp) ) )

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 128 );

   cCharsSlice slice = cs_c_( "abc", "def", "gh", "ij", "klmn", "opq" );

   expect_c_( record_chars_slice_c_( rec, slice, "" ) );
   expect_( rec, "abcdefghijklmnopq" );
   reset_recorder_c( rec );

   expect_c_( record_chars_slice_c_( rec, slice, "-" ) );
   expect_( rec, "abc-def-gh-ij-klmn-opq" );
   reset_recorder_c( rec );

   expect_c_( record_chars_slice_c_( rec, slice, " - " ) );
   expect_( rec, "abc - def - gh - ij - klmn - opq" );
   reset_recorder_c( rec );

   return finish_tap_c_();
}
