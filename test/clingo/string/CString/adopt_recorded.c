#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   cRecorder* rec = &dyn_heap_recorder_c_( 10 );

   expect_c_( recorder_cap_c( rec ) == 10 );
   expect_c_( rec->space == 10 );

   expect_c_( write_cstr_c_( rec, "a " ) );
   expect_c_( write_rune_c_( rec, rune_c( "⌂" ) ) );
   expect_c_( write_cstr_c_( rec, " with " ) );

   expect_c_( count_runes_c( recorded_chars_c( rec ) ) == 9 );
   expect_c_( rec->pos == 11 );

   int64_t mark = rec->pos;

   cRecorder* buf = &recorder_c_( 128 );
   write_int8_c_( buf, 2 );
   expect_c_( write_recorded_c_( rec, buf ) );
   expect_c_( write_cstr_c_( rec, " Windows" ) );
   expect_c_( write_char_c_( rec, '!' ) );

   expect_c_( recorded_is_c( rec, "a ⌂ with 2 Windows!" ) );

   expect_c_( count_runes_c( recorded_chars_c( rec ) ) == 19 );
   expect_c_( rec->pos == 21 );
   expect_c_( move_recorder_to_c( rec, mark ) );
   expect_c_( count_runes_c( recorded_chars_c( rec ) ) == 9 );
   expect_c_( rec->pos == 11 );
   
   expect_c_( write_cstr_c_( rec, "1 door!" ) );

   CString* str = adopt_recorded_c( rec );
   expect_c_( string_is_c( str, "a ⌂ with 1 door!" ) );
   expect_c_( recorder_cap_c( rec ) == 0 );
   expect_c_( rec->space == 0 );
   expect_c_( rec->mem == NULL );

   release_all_c_( str );

   return finish_tap_c_();
}
