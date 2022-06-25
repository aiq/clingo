#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------ init recorder
   cRecorder* rec = &recorder_c_( 10 );
   expect_c_( rec->pos == 0 );
   expect_c_( rec->space == 10 );
   expect_c_( is_empty_c_( recorded_chars_c( rec ) ) );

   // -------------------------------------------------------------- record pads
   expect_c_( record_pad_c( rec, '-', 3 ) );
   expect_c_( record_pad_c( rec, 'a', 1 ) );
   expect_c_( record_pad_c( rec, 'b', 2 ) );
   expect_c_( record_pad_c( rec, 'x', 0 ) );
   expect_c_( record_pad_c( rec, 'a', 1 ) );

   expect_c_( rec->pos == 7 ); // 3 + 1 + 2 + 1
   expect_c_( rec->space == 3 );

   cChars recorded = recorded_chars_c( rec );
   expect_c_( recorded.s == 7 );
   expect_c_( chars_is_c( recorded, "---abba" ) );

   // ------------------------------------------------ try to record to long pad
   expect_c_( not record_pad_c( rec, '-', 4 ) );

   // ------------------------------------------------------------ fill with pad
   expect_c_( record_pad_c( rec, '-', rec->space ) );

   expect_c_( rec->pos == 10 );
   expect_c_( rec->space == 0 );

   recorded = recorded_chars_c( rec );
   expect_c_( recorded.s == 10 );
   expect_c_( chars_is_c( recorded, "---abba---" ) );

   return finish_tap_c_();
}
