#include "clingo/lang/expect.h"
#include "clingo/type/int16.h"

int main( void )
{
   init_tap_c_();

   cInt16Slice slice = slice_c_( int16_t, -3016, 1838, -20915, -1739, 24879,
                                          -1734, 5126, 1838, 1958, 1983, -16080,
                                          -20645, 1838, -92 );
   cVarInt16Slice varSlice = scalars_c_( slice.s, int16_t );
   require_c_( set_var_int16_slice_c( varSlice, slice ), slice.s );

   // --------------------------------------------------------- count_eq_int16_c
   expect_equal_c_( count_eq_int16_c( slice, 1838 ), 3 );
   expect_equal_c_( count_eq_int16_c( slice, 1839 ), 0 );

   // ------------------------------------------------------------- find_int16_c
  

   // ------------------------------------------------ max_int16_c / min_int16_c

   // ---------------------------------------------- quicksort_var_int16_slice_c

   // ------------------------------------------------ reverse_var_int16_slice_c

   // ------------------------------------------------- rotate_var_int16_slice_c


   return finish_tap_c_();
}
