#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------ init recorder
   cRecorder* rec = &recorder_c_( 6 );
   expect_at_c_( rec->pos == 0 );
   expect_at_c_( rec->space == 6 );
   expect_at_c_( is_empty_c_( recorded_chars_c( rec ) ) );

   // ------------------------------------------------------------ record 3 char
   expect_at_c_( record_char_c( rec, 'a' ) );
   expect_at_c_( record_char_c( rec, 'b' ) );
   expect_at_c_( record_char_c( rec, 'c' ) );

   expect_at_c_( rec->pos == 3 );
   expect_at_c_( rec->space == 3 );

   cChars recorded = recorded_chars_c( rec );
   expect_at_c_( recorded.s == 3 );
   expect_at_c_( chars_is_c( recorded, "abc" ) );

   // ------------------------------------------------------ fill space with '-'
   while ( record_char_c( rec, '-' ) ){}

   expect_at_c_( rec->pos == 6 );
   expect_at_c_( rec->space == 0 );

   recorded = recorded_chars_c( rec );
   expect_at_c_( recorded.s == 6 );
   expect_at_c_( chars_is_c( recorded, "abc---" ) );

   return finish_tap_c_();
}
