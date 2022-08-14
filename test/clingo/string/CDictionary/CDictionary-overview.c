#include "clingo/io/print.h"
#include "clingo/lang/expect.h"
#include "clingo/string/CDictionary.h"

TEMP_SLICE_DEF_C_(
   input,
   {
      CString* k;
      CString* v;
   }
)
#define i_( ... ) ((input){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   CDictionary* dict = retain_c( make_dictionary_c( 4, 0.5f ) );

   inputSlice inputs = slice_c_( input,
      i_( lit_c( "Germany" ), lit_c( "Deutschland" ) ),
      i_( lit_c( "Spain" ), lit_c( "Spanien" ) ),
      i_( lit_c( "France" ), lit_c( "Frankreich" ) ),
      i_( lit_c( "Germany" ), lit_c( "Alemania" ) )
   );
   for_each_c_( input const* ,i, inputs )
   {
      require_c_( i->k and i->v );
      require_c_( set_on_dictionary_c( dict, i->k, i->v ) );
   }

   CString const* key;
   CString const* val;
   iterate_map_c_( itr, key, val, dict, next_in_dictionary_c )
   {
      cRecorder* rec = &recorder_c_( 128 );
      write_c_( rec, "{s} -> {s}", scstr_c( key ), scstr_c( val ) );
      println_recorded_c( rec );
   }

   require_c_( remove_via_cstr_from_dictionary_c( dict, "France" ) );

   release_c( dict );

   return finish_tap_c_();
}
