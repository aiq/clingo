#include "clingo/lang/expect.h"
#include "clingo/type/int32.h" // bsearch_int32_c

int main( void )
{
   init_tap_c_();

   tap_note_c( "even slice test" );
   {
      cInt32Slice evenSlice = slice_c_( int32_t,
         -30, -20, -10, 0, 10, 20, 30, 40
      );
      int32_t val = -30;
      for ( int64_t index = 0; index < evenSlice.s; ++index )
      {
         int32_t const* ptr = bsearch_int32_c( evenSlice, val );
         expect_c_( index_of_c_( evenSlice, ptr ) == index );
         val += 10;
      }
   }

   tap_note_c( "odd slice test" );
   {
      cInt32Slice oddSlice = slice_c_( int32_t, -30, -20, -10, 0, 10, 20, 30 );
      int32_t val = -30;
      for ( int64_t index = 0; index < oddSlice.s; ++index )
      {
         int32_t const* ptr = bsearch_int32_c( oddSlice, val );
         expect_c_( index_of_c_( oddSlice, ptr ) == index );
         val += 10;
      }
   }

   return finish_tap_c_();
}
