#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"
#include "clingo/string/CStringBuilder.h"

int main( void )
{
   init_tap_c_();

   CStringBuilder* builder = retain_c( make_string_builder_c( 10 ) );
   cRecorder* rec = &recorder_c_( 128 );

   expect_c_( string_builder_cap_c( builder ) == 10 );
   expect_c_( string_builder_space_c( builder ) == 10 );

   expect_c_( append_cstr_c( builder, "a " ) );
   expect_c_( append_rune_c( builder, rune_c( "⌂" ) ) );
   expect_c_( append_cstr_c( builder, " with " ) );

   write_int8_c_( rec, 2 );
   expect_c_( append_recorded_c( builder, rec ) );
   expect_c_( append_cstr_c( builder, " Windows" ) );
   expect_c_( append_char_c( builder, '!' ) );

   cChars built = built_chars_c( builder );
   expect_c_( chars_is_c( built, "a ⌂ with 2 Windows!" ) );

   CString* str = turn_into_string_c( builder );
   expect_c_( string_is_c( str, "a ⌂ with 2 Windows!" ) );
   expect_c_( string_builder_cap_c( builder ) == 0 );
   expect_c_( string_builder_byte_length_c( builder ) == 0 );

   release_all_c_( builder, str );

   return finish_tap_c_();
}
