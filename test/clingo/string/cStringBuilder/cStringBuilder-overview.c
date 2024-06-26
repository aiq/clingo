#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"
#include "clingo/string/cStringBuilder.h"

int main( void )
{
   init_tap_c_();

   cStringBuilder* b = &(cStringBuilder){0};
   init_string_builder_c( b, 10 );

   expect_at_c_( string_builder_cap_c( b ) == 10 );
   expect_at_c_( string_builder_space_c( b ) == 10 );

   expect_at_c_( append_cstr_c( b, "a " ) );
   expect_at_c_( append_rune_c( b, rune_c( "⌂" ) ) );
   expect_at_c_( append_cstr_c( b, " with " ) );

   expect_at_c_( string_builder_length_c( b ) == 9 );
   expect_at_c_( string_builder_byte_length_c( b ) == 11 );
   cStringBuilderMark mark = mark_string_builder_c( b );

   cRecorder* rec = &recorder_c_( 128 );
   write_int8_c_( rec, 2 );
   expect_at_c_( append_recorded_c( b, rec ) );
   expect_at_c_( append_cstr_c( b, " Windows" ) );
   expect_at_c_( append_char_c( b, '!' ) );

   cChars built = built_chars_c( b );
   expect_at_c_( chars_is_c( built, "a ⌂ with 2 Windows!" ) );

   expect_at_c_( string_builder_length_c( b ) == 19 );
   expect_at_c_( string_builder_byte_length_c( b ) == 21 );
   expect_at_c_( reset_string_builder_to_c( b, mark ) );
   expect_at_c_( string_builder_length_c( b ) == 9 );
   expect_at_c_( string_builder_byte_length_c( b ) == 11 );
   
   expect_at_c_( append_cstr_c( b, "1 door!" ) );

   CString* str = turn_into_string_c( b );
   expect_at_c_( string_is_c( str, "a ⌂ with 1 door!" ) );
   expect_at_c_( string_builder_cap_c( b ) == 0 );
   expect_at_c_( string_builder_byte_length_c( b ) == 0 );
   expect_at_c_( b->rec.mem == NULL );

   release_all_c_( str );

   return finish_tap_c_();
}
