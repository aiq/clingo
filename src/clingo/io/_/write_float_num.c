#include "write_num.h"

#include "cWriteNumFormat.h"
#include "clingo/io/write.h"
#include "clingo/io/write_type.h"

/*******************************************************************************
   "+f.3q(20r_)"
   [sign][type][quote][precision][cell]

   https://randomascii.wordpress.com/2012/03/08/float-precisionfrom-zero-to-100-digits-2/
   http://www.serpentine.com/blog/2011/06/29/here-be-dragons-advances-in-problems-you-didnt-even-know-you-had/
   https://github.com/floitsch/double-conversion
*******************************************************************************/

bool write_float_num_c( cRecorder rec[static 1],
                        double d,
                        char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );

   cVarChars valBuf = scalars_c_( cWRITE_NUM_VALUE_BUF_SIZE_, char );
   int64_t len = 0;

   // parse format -------------------------------------------------------------
   cWriteNumFormat numFmt;
   if ( not init_write_float_format_c( &numFmt, fmt ) )
   {
      return set_recorder_error_c( rec, c_InvalidWriteFormat );
   }
   // optional quote at begin --------------------------------------------------
   if ( numFmt.quote )
   {
      set_if_c_( valBuf, len, *numFmt.quote );
      ++len;
   }

   cRecorder* recFmt = &recorder_c_( 16 );
   {
      record_char_c( recFmt, '%' );

      // optional sign ---------------------------------------------------------
      if ( numFmt.sign )
      {
         record_char_c( recFmt, '+' );
      }

      // optional precision ----------------------------------------------------
      if ( numFmt.precision >= 0 )
      {
         record_char_c( recFmt, '.' );
         write_int16_c_( recFmt, numFmt.precision );
      }

      // type ------------------------------------------------------------------
      if ( numFmt.type == 'x' )
      {
         record_char_c( recFmt, 'a' );
      }
      else if ( numFmt.type == 'X' )
      {
         record_char_c( recFmt, 'A' );
      }
      else
      {
         record_char_c( recFmt, numFmt.type );
      }
   }

   cVarChars numBuf = mid_c_( cVarChars, valBuf, len );
   size_t size;
   if ( not int64_to_size_c( numBuf.s, &size ) ) return false;
    
   len += snprintf( numBuf.v, size, turn_into_cstr_c( recFmt ), d );

   // optional quote at end ----------------------------------------------------
   if ( numFmt.quote )
   {
      set_if_c_( valBuf, len, *numFmt.quote );
      ++len;
   }
   valBuf.s = len;

   each_c_( char*, c, valBuf )
   {
      if ( *c == '.' or *c == ',' )
         *c = numFmt.decimal;
   }

   // write the value in cell or plain -----------------------------------------
   cChars valChars = as_c_( cChars, valBuf );
   if ( numFmt.cell.size > 0 )
   {
      return write_ascii_into_cell_c( rec, valChars, &numFmt.cell );
   }

   return record_chars_c( rec, valChars )
      ? true
      : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

