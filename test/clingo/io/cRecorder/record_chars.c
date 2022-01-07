#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 6 );

   // --------------------------------------------------------------- record abc
   expect_c_( record_chars_c( rec, c_c( "abc" ) ) );
   expect_c_( rec->pos == 3 );
   expect_c_( rec->space == 3 );

   cChars recorded = recorded_chars_c( rec );
   expect_c_( chars_is_c( recorded, "abc" ) );

   // ------------------------------------------------------- record empty chars
   expect_c_( record_chars_c_( rec, "" ) );
   expect_c_( rec->pos == 3 );
   expect_c_( rec->space == 3 );

   // ---------------------------------------------- try to record to long chars
   cChars defg = c_c( "defg" );
   expect_c_( not record_chars_c( rec, defg ) ); // to large
   expect_c_( rec->pos == 3 );
   expect_c_( rec->space == 3 );

   // --------------------------------------------- fill recorder with sub chars
   cChars subChars = left_chars_c( defg, rec->space );
   expect_c_( record_chars_c( rec, subChars ) );
   expect_c_( rec->pos == 6 );
   expect_c_( rec->space == 0 );

   return finish_tap_c_();
}
