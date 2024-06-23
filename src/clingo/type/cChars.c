#include "clingo/type/cChars.h"

#include <string.h>

#include "clingo/lang/algo.h"
#include "clingo/lang/func.h"
#include "clingo/type/uint64.h"

#include "clingo/io/print.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall 
*******************************************************************************/

extern inline cChars c_c( char const cstr[static 1] );

bool chars_is_c( cChars chars, char const cstr[static 1] )
{
   return eq_c( cmp_chars_c( chars, c_c( cstr ) ) );
}

bool cstr_is_any_char_c( char const cstr[static 1], cChars set )
{
   char const* found = find_char_c( set, *cstr );
   return found and *(++cstr) == '\0';
}

extern inline bool cstr_is_c( char const cstr[static 1],
                              char const exp[static 1] );

extern inline bool cstr_is_char_c( char const cstr[static 1], char c );

bool eq_chars_c( cChars a, cChars b )
{
   return eq_c( cmp_chars_c( a, b ) );
}

char* make_cstr_c( cVarChars buf, cChars cs )
{
   if ( buf.s <= cs.s ) return NULL;
   buf.s = set_chars_c( buf, cs );
   buf.v[ buf.s ] = '\0';
   return buf.v;
}

/*******************************************************************************
 algo
*******************************************************************************/

CMP_SLICE_C_(
   cmp_chars_c,   // FuncName
   cChars,        // SliceType
   char const,    // ValueType
   cmp_char_c,    // CmpFunc
   do_deref_c_    // DoDeref
)

COUNT_EQ_C_(
   count_eq_char_c,  // FuncName
   cChars,           // SliceType
   char const,       // ValueType
   char,             // SearchType
   cmp_char_c,       // CmpFunc
   do_deref_c_       // DoDeref
)

ENDS_WITH_C_(
   chars_ends_with_c,   // FuncName
   cChars,              // SliceType
   char const,          // ValueType
   cmp_char_c,          // CmpFunc
   do_deref_c_          // DoDeref
)

char const* find_any_char_c( cChars chars, cChars set )
{
   each_c_( char const*, outItr, chars )
   {
      each_c_( char const*, inItr, set )
      {
         if ( *outItr == *inItr ) return outItr;
      }
   }
   return NULL;
}

FIND_VAL_C_(
   find_char_c,   // FuncName
   cChars,        // SliceType
   char const,    // ValueType
   char,          // SearchType
   cmp_char_c,    // CmpFunc
   do_deref_c_    // DoDeref
)

INDEX_OF_SLICE_C_(
   index_of_chars_c, // FuncName
   cChars,           // SliceType
   char const,       // ValueType
   cmp_char_c,       // CmpFunc
   do_deref_c_       // DoDeref
)

QSORT_C_(
   qsort_chars_c, // FuncName
   cVarChars,     // SliceType
   char,          // ValueType
   cmp_char_c,    // CmpFunc
   do_deref_c_    // DoDeref
)

REMOVE_C_(
   remove_char_c, // FuncName
   cVarChars,     // SliceType
   char           // ValueType
)

REVERSE_C_(
   reverse_chars_c,  // FuncName
   cVarChars,        // SliceType
   char              // ValueType
)

ROTATE_C_(
   rotate_chars_c,   // FuncName
   cVarChars,        // SliceType
   char              // ValueType
)

STARTS_WITH_C_(
   chars_starts_with_c, // FuncName
   cChars,              // SliceType
   char const,          // ValueType
   cmp_char_c,          // CmpFunc
   do_deref_c_          // DoDeref
)

SET_SLICE_C_(
   set_chars_c,   // FuncName
   cVarChars,     // VarSliceType
   cChars         // SliceType
)

TAKE_C_(
   take_char_c,   // FuncName
   cVarChars,     // SliceType
   char           // ValueType
)

/*******************************************************************************
 trim
*******************************************************************************/

cChars trim_any_char_c( cChars chars, cChars set )
{
   chars = trim_any_char_left_c( chars, set );
   chars = trim_any_char_right_c( chars, set );
   return chars;
}

cChars trim_any_char_left_c( cChars chars, cChars set )
{
   if ( is_empty_c_( chars ) ) return chars;

   char const* itr = begin_c_( chars );
   char const* end = end_c_( chars );
   while ( itr < end and find_char_c( set, *itr ) )
   {
      ++itr;
   }
   return (cChars)atween_c_( itr, end );
}

cChars trim_any_char_right_c( cChars chars, cChars set )
{
   if ( is_empty_c_( chars ) ) return chars;

   char const* itr = rbegin_c_( chars );
   char const* end = rend_c_( chars );
   while ( itr > end and find_char_c( set, *itr ) )
   {
      --itr;
   }
   return (cChars)atween_c_( begin_c_( chars ), itr+1 );
}

cChars trim_char_match_c( cChars chars, c_check_char check )
{
   chars = trim_char_match_left_c( chars, check );
   chars = trim_char_match_right_c( chars, check );
   return chars;
}

cChars trim_char_match_left_c( cChars chars, c_check_char check )
{
   if ( is_empty_c_( chars ) ) return chars;

   char const* itr = begin_c_( chars );
   char const* end = end_c_( chars );
   while ( itr < end and check( *itr ) )
   {
      ++itr;
   }
   return (cChars)atween_c_( itr, end );
}

cChars trim_char_match_right_c( cChars chars, c_check_char check )
{
   if ( is_empty_c_( chars ) ) return chars;

   char const* itr = rbegin_c_( chars );
   char const* end = rend_c_( chars );
   while ( itr > end and check( *itr ) )
   {
      --itr;
   }
   return (cChars)atween_c_( begin_c_( chars ), itr+1 );
}
