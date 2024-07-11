#ifndef CLINGO_IO_INTERN_WRITE_INT_H
#define CLINGO_IO_INTERN_WRITE_INT_H

#include "cWriteNumFormat.h"
#include "write_num.h"

#define WRITE_INT_C_(                                                          \
   Type, FuncName, Dec, ConvType                                               \
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
   cVarChars numBuf = mid_c_( cVarChars, valBuf, len );                        \
   /* decimal value ------------------------------------------------------- */ \
   if ( numFmt.type == 'd' )                                                   \
   {                                                                           \
      if ( numFmt.sign )                                                       \
      {                                                                        \
         len += snprintf( numBuf.v, (size_t)numBuf.s, "%+"Dec, val );          \
      }                                                                        \
      else                                                                     \
      {                                                                        \
         len += snprintf( numBuf.v, (size_t)numBuf.s, "%"Dec, val );           \
      }                                                                        \
   }                                                                           \
   /* memory value -------------------------------------------------------- */ \
   else if ( numFmt.memory )                                                   \
   {                                                                           \
      ConvType memVal = (ConvType)val;                                         \
                                                                               \
      if ( numFmt.type == 'x' )                                                \
      {                                                                        \
         len += write_hex_c( memVal, false, numBuf );                          \
      }                                                                        \
      else if ( numFmt.type == 'X' )                                           \
      {                                                                        \
         len += write_hex_c( memVal, true, numBuf );                           \
      }                                                                        \
      else if ( numFmt.type == 'o' )                                           \
      {                                                                        \
         len += write_oct_c( memVal, numBuf );                                 \
      }                                                                        \
      else if ( numFmt.type == 'b' )                                           \
      {                                                                        \
         len += write_bin_c( memVal, false, numBuf );                          \
      }                                                                        \
      else if ( numFmt.type == 'B' )                                           \
      {                                                                        \
         len += write_bin_c( memVal, true, numBuf );                           \
      }                                                                        \
   }                                                                           \
   /* other value --------------------------------------------------------- */ \
   else /* value */                                                            \
   {                                                                           \
      bool negative = val < 0;                                                 \
      uint64_t positiveVal = plusval_c( val );                                 \
                                                                               \
      if ( numFmt.sign or negative )                                           \
      {                                                                        \
         *(numBuf.v) = negative ? '-'                                          \
                                : '+';                                         \
         ++len;                                                                \
         numBuf = mid_c_( cVarChars, numBuf, 1 );                              \
      }                                                                        \
                                                                               \
      if ( numFmt.type == 'x' )                                                \
      {                                                                        \
         len += write_hex_c( positiveVal, false, numBuf );                     \
      }                                                                        \
      else if ( numFmt.type == 'X' )                                           \
      {                                                                        \
         len += write_hex_c( positiveVal, true, numBuf );                      \
      }                                                                        \
      else if ( numFmt.type == 'o' )                                           \
      {                                                                        \
         len += write_oct_c( positiveVal, numBuf );                            \
      }                                                                        \
      else if ( numFmt.type == 'b' )                                           \
      {                                                                        \
         len += write_bin_c( positiveVal, false, numBuf );                     \
      }                                                                        \
      else if ( numFmt.type == 'B' )                                           \
      {                                                                        \
         len += write_bin_c( positiveVal, true, numBuf );                      \
      }                                                                        \
   }                                                                           \
                                                                               \
   /* optional quote at end ----------------------------------------------- */ \
   if ( numFmt.quote )                                                         \
   {                                                                           \
      set_if_c_( valBuf, len, *numFmt.quote );                                    \
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
