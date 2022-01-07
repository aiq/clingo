#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cCharsToken.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* text;
      cCharsSlice set;
      bool ignoreEmpty;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

#include "clingo/io/print.h"
#define pln_( ... ) pjotln_c_( xyz, 1024, __VA_ARGS__ )

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "AlBeGaDeEpZeEtThIoKaLaMyNyXiOmPiRhSiTaYpPhChPsOm",
          cs_c_( "De", "Ep", "Xi", "Ta" ), true,
          "AlBeGa.ZeEtThIoKaLaMyNy.OmPiRhSi.YpPhChPsOm" ),
      t_( "AlBeGaDeEpZeEtThIoKaLaMyNyXiOmPiRhSiTaYpPhChPsOm",
          cs_c_( "De", "Ep", "Xi", "Ta" ), false,
          "AlBeGa..ZeEtThIoKaLaMyNy.OmPiRhSi.YpPhChPsOm" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 128 );

      cCharsToken tok;
      init_cstr_token_c( &tok, t->text );
      while ( next_token_till_any_c( &tok, t->set ) )
      {
         if ( t->ignoreEmpty and is_empty_c_( tok.x ) ) continue;

         record_chars_c( rec, tok.x );
         if ( not is_last_token_c( &tok ) )
         {
            record_char_c( rec, '.' );
         }
      }
      bool res = recorded_is_c( rec, t->exp );
      tap_descf_c( res, "test expected: %s", t->exp );
   }

   return finish_tap_c_();
}
