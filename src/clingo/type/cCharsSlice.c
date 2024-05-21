#include "clingo/type/cCharsSlice.h"

#include "clingo/io/cRecorder.h"
#include "clingo/lang/algo.h"
#include "clingo/type/cRune.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall 
*******************************************************************************/

cCharsSlice init_chars_slice_c( cVarCharsSlice slice,
                                int64_t n,
                                char const* arr[static 1] )
{
   if ( n > slice.s ) return (cCharsSlice)empty_c_();

   for ( int64_t i = 0; i < n; ++i )
   {
      slice.v[i] = c_c( arr[i] );
   }

   slice.s = n;
   return as_c_( cCharsSlice, slice );
}

/*******************************************************************************
 algo
*******************************************************************************/

COUNT_EQ_C_(
   count_eq_chars_c, // FuncName
   cCharsSlice,      // SliceType
   cChars const,     // ValueType
   cChars,           // SearchType
   cmp_chars_c,      // CmpFunc
   do_deref_c_       // DoDeref
)

FIND_VAL_C_(
   find_chars_c,  // FuncName
   cCharsSlice,   // SliceType
   cChars const,  // ValueType
   cChars,        // SearchType
   cmp_chars_c,   // CmpFunc
   do_deref_c_    // DoDeref
)

QSORT_C_(
   qsort_chars_slice_c, // FuncName
   cVarCharsSlice,      // SliceType
   cChars,              // ValueType
   cmp_chars_c,         // CmpFunc
   do_deref_c_          // DoDeref
)

/*******************************************************************************

*******************************************************************************/

int64_t count_chars_slice_c( cCharsSlice slice )
{
   int64_t result = 0;
   for_each_c_( cChars const*, chars, slice )
   {
      result += chars->s;
   }
   return result;
}

int64_t count_chars_slice_runes_c( cCharsSlice slice )
{
   int64_t result = 0;
   for_each_c_( cChars const*, chars, slice )
   {
      int64_t tmp = count_runes_c( *chars );
      if ( tmp < 0 ) return -1;

      result += tmp;
   }
   return result;
}

/*******************************************************************************

*******************************************************************************/

bool chars_ends_with_any_c( cChars chars, cCharsSlice slice )
{
   for_each_c_( cChars const*, any, slice )
   {
      if ( chars_ends_with_c( chars, *any ) ) return true;
   }
   return false;
}

extern inline bool chars_is_any_c( cChars chars, cCharsSlice slice );

bool chars_starts_with_any_c( cChars chars, cCharsSlice slice )
{
   for_each_c_( cChars const*, any, slice )
   {
      if ( chars_starts_with_c( chars, *any ) ) return true;
   }
   return false;
}

int64_t index_of_any_chars_c( cChars chars, cCharsSlice slice )
{
   char const* beg = begin_c_( chars );
   char const* end = end_c_( chars );
   for ( ; beg < end; ++beg )
   {
      cChars sub = atween_c_( beg, end );
      if ( chars_starts_with_any_c( sub, slice ) )
      {
         return index_of_c_( chars, beg );
      }
   }

   return -1;
}

cChars join_chars_slice_c( cCharsSlice slice, cChars sep, cVarChars buf )
{
   cRecorder* rec = &make_fix_recorder_c_( buf.s, buf.v );
   record_chars_slice_c( rec, slice, sep );
   return recorded_chars_c( rec );
}

