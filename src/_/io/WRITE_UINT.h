#ifndef CLINGO_INTERN_IO_WRITE_UINT_H
#define CLINGO_INTERN_IO_WRITE_UINT_H

#include "_/io/cWriteNumFormat.h"
#include "_/io/write_num.h"

#define WRITE_UINT_C_(                                                         \
   Type, FuncName, Dec                                                         \
)                                                                              \
bool FuncName( cRecorder rec[static 1],                                        \
               Type val,                                                       \
               char const fmt[static 1] )                                      \
{                                                                              \
   must_exist_c_( rec );                                                       \
   must_exist_c_( fmt );                                                       \
                                                                               \
   /* parse format -------------------------------------------------------- */ \
   cWriteNumFormat numFmt;                                                     \
   if ( not init_write_int_format_c( &numFmt, fmt ) )                          \
   {                                                                           \
      return set_recorder_error_c( rec, c_InvalidWriteFormat );                \
   }                                                                           \
                                                                               \
   cVarChars valBuf = scalars_c_( cWRITE_NUM_VALUE_BUF_SIZE_, char );          \
   int64_t len = 0;                                                            \
                                                                               \
   /* optional quote at begin --------------------------------------------- */ \
   if ( numFmt.quote )                                                         \
   {                                                                           \
      set_if_c_( valBuf, len, *numFmt.quote );                                    \
      ++len;                                                                   \
   }                                                                           \
                                                                               \
   /* optional sign ------------------------------------------------------- */ \
   cVarChars numBuf = mid_c_( cVarChars, valBuf, len );                        \
   if ( numFmt.sign and not numFmt.memory )                                    \
   {                                                                           \
      *(numBuf.v) = '+';                                                       \
      ++len;                                                                   \
      numBuf = mid_c_( cVarChars, numBuf, 1 );                                 \
   }                                                                           \
                                                                               \
   /* value --------------------------------------------------------------- */ \
   if ( numFmt.type == 'd' )                                                   \
   {                                                                           \
      len += snprintf( numBuf.v, (size_t)numBuf.s, "%" Dec, val );             \
   }                                                                           \
   else if ( numFmt.type == 'x' )                                              \
   {                                                                           \
      len += write_hex_c( val, false, numBuf );                                \
   }                                                                           \
   else if ( numFmt.type == 'X' )                                              \
   {                                                                           \
      len += write_hex_c( val, true, numBuf );                                 \
   }                                                                           \
   else if ( numFmt.type == 'o' )                                              \
   {                                                                           \
      len += write_oct_c( val, numBuf );                                       \
   }                                                                           \
   else if ( numFmt.type == 'b' )                                              \
   {                                                                           \
      len += write_bin_c( val, false, numBuf );                                \
   }                                                                           \
   else if ( numFmt.type == 'B' )                                              \
   {                                                                           \
      len += write_bin_c( val, true, numBuf );                                 \
   }                                                                           \
                                                                               \
   /* optional quote at end ----------------------------------------------- */ \
   if ( numFmt.quote )                                                         \
   {                                                                           \
      set_if_c_( valBuf, len, *numFmt.quote );                                 \
      ++len;                                                                   \
   }                                                                           \
   valBuf.s = len;                                                             \
                                                                               \
   /* write the value in cell or plain ------------------------------------ */ \
   cChars valChars = as_c_( cChars, valBuf );                                  \
                                                                               \
   if ( numFmt.cell.size > 0 )                                                 \
   {                                                                           \
      return write_ascii_into_cell_c( rec, valChars, &numFmt.cell );           \
   }                                                                           \
                                                                               \
   return record_chars_c( rec, valChars )                                      \
      ? true                                                                   \
      : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );                 \
}


#endif
