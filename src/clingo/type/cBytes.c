#include "clingo/type/cBytes.h"

#include <stddef.h>
#include <string.h>

#include "clingo/lang/algo.h"
#include "clingo/lang/func.h"
#include "clingo/lang/math.h"
#include "clingo/type/c_ByteOrder.h"
#include "clingo/io/print.h"

/******************************************************************************/
static inline cByte left_shift_pair( cByte leftByte,
                                     cByte rightByte,
                                     int64_t offset )
{
   union { cByte bytes[ 8 ]; uint64_t doubleByte; } shiftType;

   if ( system_order_is_c( c_LittleEndian ) )
   {
      shiftType.bytes[ 7 ] = leftByte;
      shiftType.bytes[ 6 ] = rightByte;
      shiftType.doubleByte = shiftType.doubleByte << offset;
      return shiftType.bytes[ 7 ];
   }
   else
   {
      shiftType.bytes[ 6 ] = leftByte;
      shiftType.bytes[ 7 ] = rightByte;
      shiftType.doubleByte = shiftType.doubleByte << offset;
      return shiftType.bytes[ 6 ];
   }
}

static inline void left_shift_bits( cVarBytes slice,
                                    int64_t offset,
                                    cByte fillValue )
{
   const int64_t bitOffset = offset % 8;
   const int64_t byteOffset = offset / 8;
   const int64_t firstBytePos = 0;
   const int64_t lastBytePos = ( slice.s - 1 ) - byteOffset;
   const int64_t n = slice.s - byteOffset;
   size_t size;
   if ( not int64_to_size_c( n, &size ) ) return;

   memmove( slice.v, slice.v + byteOffset, size );

   for ( int64_t i = firstBytePos; i <= lastBytePos; ++i )
   {
      const cByte leftByte = slice.v[ i ];
      const cByte rightByte = ( i < lastBytePos ) ? slice.v[ i + 1 ]
                                                  : 0x00;
      slice.v[ i ] = left_shift_pair( leftByte, rightByte, bitOffset );
   }

   const int64_t max = ( slice.s * 8 ) - 1;
   cRange range = closed_range_c_( max - ( offset - 1 ), max );
   set_bytes_bits_c( slice, range, fillValue );
}

static inline cByte right_shift_pair( cByte leftByte,
                                      cByte rightByte,
                                      int64_t offset )
{
   union { cByte bytes[ 2 ]; uint16_t doubleByte; } shiftType;

   if ( system_order_is_c( c_LittleEndian ) )
   {
      shiftType.bytes[ 1 ] = leftByte;
      shiftType.bytes[ 0 ] = rightByte;
      shiftType.doubleByte = shiftType.doubleByte >> offset;
      return shiftType.bytes[ 0 ];
   }
   else
   {
      shiftType.bytes[ 0 ] = leftByte;
      shiftType.bytes[ 1 ] = rightByte;
      shiftType.doubleByte = shiftType.doubleByte >> offset;
      return shiftType.bytes[ 1 ];
   }
}

static inline void right_shift_bits( cVarBytes slice,
                                     int64_t offset,
                                     cByte fillValue )
{
   const int64_t bitOffset = offset % 8;
   const int64_t byteOffset = offset / 8;
   const int64_t firstBytePos = byteOffset;
   const int64_t lastBytePos = slice.s - 1;
   const int64_t n = slice.s - byteOffset;
   size_t size;
   if ( not int64_to_size_c( n, &size ) ) return;

   memmove( slice.v + byteOffset, slice.v, size );

   for ( int64_t i = lastBytePos; i >= firstBytePos; --i )
   {
      const cByte leftByte = ( i > 0 ) ? slice.v[ i - 1 ]
                                       : 0x00;
      const cByte rightByte = slice.v[ i ];
      slice.v[ i ] = right_shift_pair( leftByte, rightByte, bitOffset );
   }

   cRange range = closed_open_range_c_( 0, offset );
   set_bytes_bits_c( slice, range, fillValue );
}

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 bit
*******************************************************************************/

extern inline cByte get_bytes_bit_c( cBytes slice, int64_t pos );

extern inline void set_bytes_bit_c( cVarBytes slice, int64_t pos, cByte bit );

void set_bytes_bits_c( cVarBytes slice, cRange range, cByte bit )
{
   must_be_c_( ( range.max <= ( slice.s * 8 ) ) and
               ( range_size_c( range ) > 0 ) );

   int64_t const minByte = range.min / 8;
   int64_t const maxByte = range.max / 8;

   if ( minByte == maxByte ) // ----------------------------- minByte == maxByte
   {
      cByte byte = slice.v[ minByte ];
      const int64_t minBit = range.min % 8;
      const int64_t maxBit = range.max % 8;
      for ( int64_t pos = minBit; pos <= maxBit; ++pos )
      {
         byte = set_byte_bit_c( byte, pos, bit );
      }
      slice.v[ minByte ] = byte;
      return;
   }

   // ------------------------------------------------------- minByte != maxByte
   // minByte
   {
      if ( bit == 1 )
      {
         static const cByte mask[ 8 ] = { 0xFF, 0x7F, 0x3F, 0x1F,
                                          0x0F, 0x07, 0x03, 0x01 };
         slice.v[ minByte ] = slice.v[ minByte ] | mask[ range.min % 8 ];
      }
      else
      {
         static const cByte mask[ 8 ] = { 0x00, 0x80, 0xC0, 0xE0,
                                          0xF0, 0xF8, 0xFC, 0xFE };
         slice.v[ minByte ] = slice.v[ minByte ] & mask[ range.min % 8 ];
      }
   }
   // bytes between
   {
      size_t size;
      if ( not int64_to_size_c( ( ( maxByte - minByte ) - 1 ), &size ) ) return;
 
      const cByte fillValue = ( bit == 1 ) ? 0xff
                                           : 0x00;
      memset( slice.v + minByte + 1, fillValue, size );
   }
   // maxByte
   {
      if ( bit == 1 )
      {
         static const cByte mask[ 8 ] = { 0x80, 0xC0, 0xE0, 0xF0,
                                          0xF8, 0xFC, 0xFE, 0xFF };
         slice.v[ maxByte ] = slice.v[ maxByte ] | mask[ range.max % 8 ];
      }
      else
      {
         static const cByte mask[ 8 ] = { 0x7F, 0x3F, 0x1F, 0x0F,
                                          0x07, 0x03, 0x01, 0x00 };
         slice.v[ maxByte ] = slice.v[ maxByte ] & mask[ range.max % 8 ];
      }
   }
}

void set_odd_byte_c( cVarBytes slice,
                     int64_t pos,
                     int64_t bitOffset,
                     cByte byte )
{
   const int64_t maxPos = slice.s - 1;

   cByte tmp[ 3 ];
   tmp[ 0 ] = 0x00;
   tmp[ 1 ] = slice.v[ pos ];
   tmp[ 2 ] = ( pos != maxPos ) ? slice.v[ pos + 1 ]
                                : 0x00;

   tmp[ 0 ] = left_shift_pair( tmp[ 0 ], tmp[ 1 ], bitOffset );
   tmp[ 1 ] = left_shift_pair( tmp[ 1 ], tmp[ 2 ], bitOffset );
   tmp[ 2 ] = left_shift_pair( tmp[ 2 ], 0x00, bitOffset );

   tmp[ 1 ] = byte;

   tmp[ 2 ] = right_shift_pair( tmp[ 1 ], tmp[ 2 ], bitOffset );
   tmp[ 1 ] = right_shift_pair( tmp[ 0 ], tmp[ 1 ], bitOffset );

   if ( pos == maxPos )
   {
      slice.v[ pos ] = tmp[ 1 ];
   }
   else
   {
      slice.v[ pos ] = tmp[ 1 ];
      slice.v[ pos + 1 ] = tmp[ 2 ];
   }
}

void shift_bytes_bits_c( cVarBytes slice, int64_t offset, cByte fillValue )
{
   if ( offset < 0 )
   {
      abs_c_( offset, &offset );
      left_shift_bits( slice, offset, fillValue );
   }
   else
   {
      right_shift_bits( slice, offset, fillValue );
   }
}

extern inline void toggle_bytes_bit_c( cVarBytes slice, int64_t pos );

/*******************************************************************************
 shift
*******************************************************************************/

WINDOW_C_( cByte, cVarBytes, cVarByteWindow )

void shift_bytes_c( cVarBytes slice, int64_t offset )
{
   if ( offset < 0 )
   {
      abs_c_( offset, &offset );
      cVarByteWindow window = front_window_c_( offset+1, slice );
      while ( valid_window_c_( window ) )
      {
         cByte* dst = begin_c_( window );
         cByte* src = rbegin_c_( window );
         *dst = *src;
         next_window_c_( window );
      }
   }
   else
   {
      cVarByteWindow window = back_window_c_( offset+1, slice );
      while ( valid_window_c_( window ) )
      {
         cByte* dst = rbegin_c_( window );
         cByte* src = begin_c_( window );
         *dst = *src;
         prev_window_c_( window );
      }
   }
}

/*******************************************************************************
 logic
*******************************************************************************/

extern inline bool bitand_bytes_c( cBytes a, cBytes b, cVarBytes result );

extern inline bool bitor_bytes_c( cBytes a, cBytes b, cVarBytes result );

extern inline bool compl_bytes_c( cBytes slice, cVarBytes result );

extern inline bool xor_bytes_c( cBytes a, cBytes b, cVarBytes result );

/*******************************************************************************

*******************************************************************************/

CMP_SLICE_C_(
   cmp_bytes_c,   // FuncName
   cBytes,        // SliceType
   cByte const,   // ValueType
   cmp_byte_c,    // CmpFunc
   do_deref_c_    // DoDeref
)

COUNT_EQ_C_(
   count_eq_byte_c,  // FuncName
   cBytes,       // SliceType
   cByte const,      // ValueType
   cByte,            // SearchType
   cmp_byte_c,       // CmpFunc
   do_deref_c_       // DoDeref
)

ENDS_WITH_C_(
   bytes_ends_with_c,   // FuncName
   cBytes,              // SliceType
   cByte const,         // ValueType
   cmp_byte_c,          // CmpFunc
   do_deref_c_          // DoDeref
)

FIND_VAL_C_(
   find_byte_c,   // FuncName
   cBytes,        // SliceType
   cByte const,   // ValueType
   cByte,         // SearchType
   cmp_byte_c,    // CmpFunc
   do_deref_c_    // DoDeref
)

INDEX_OF_SLICE_C_(
   index_of_bytes_c, // FuncName
   cBytes,           // SliceType
   cByte const,      // ValueType
   cmp_byte_c,       // CmpFunc
   do_deref_c_       // DoDeref
)

INSERT_VAL_C_(
   insert_byte_c,    // FuncName
   cVarBytes,        // VarSliceType
   cByte,            // ValueType
   cByte,            // InsertType
   do_not_deref_c_   // DoDeref
)

INSERT_SLICE_C_(
   insert_bytes_c,   // FuncName
   cVarBytes,        // VarSliceType
   cBytes            // SliceType
)

STARTS_WITH_C_(
   bytes_starts_with_c, // FuncName
   cBytes,              // SliceType
   cByte const,         // ValueType
   cmp_byte_c,          // CmpFunc
   do_deref_c_          // DoDeref
)
