#include "_/io/cWriteNumFormat.h"

#include "clingo/io/read_type.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool init_write_int_format_c( cWriteNumFormat numFmt[static 1],
                              char const format[static 1] )
{
   cScanner* sca = &cstr_scanner_c_( format );
   numFmt->sign = parse_sign_flag_c( sca );
   numFmt->memory = parse_memory_flag_c( sca );
   numFmt->type = parse_int_format_type_c( sca );
   numFmt->quote = parse_quote_value_c( sca );
   read_in_cell_c( sca, &numFmt->cell );

   return sca->space == 0;
}

bool init_write_float_format_c( cWriteNumFormat numFmt[static 1],
                                char const fmt[static 1] )
{
   cScanner* sca = &cstr_scanner_c_( fmt );
   numFmt->sign = parse_sign_flag_c( sca );
   numFmt->type = parse_float_format_type_c( sca );
   numFmt->precision = parse_precision_value_c( sca );
   numFmt->quote = parse_quote_value_c( sca );
   read_in_cell_c( sca, &numFmt->cell );

   return sca->space == 0;
}

void dump_write_num_format_c( cWriteNumFormat const* fmt )
{
   must_exist_c_( fmt );

   printf( "-------- FORMAT --------\n" );
   printf( "sign:       %s\n", fmt->sign ? "true" : "false" );
   printf( "memory:     %s\n", fmt->memory ? "true" : "false" );
   printf( "type:       %c\n", fmt->type );
   printf( "quote:      %s\n", fmt->quote );
   printf( "precision:  %i\n", fmt->precision );
   printf( "cell:\n" );
   printf( "   orient:  %i\n", fmt->cell.orient );
   printf( "   size:    %i\n", fmt->cell.size );
   printf( "   pad:     '%c'\n", fmt->cell.pad );
   printf( "------------------------\n" );
}

/*******************************************************************************
 parse
*******************************************************************************/

static cChars const C_IntFormats = slice_c_(
   char, 'd', 'x', 'X', 'o', 'b', 'B'
);

char parse_int_format_type_c( cScanner* sca )
{
   must_exist_c_( sca );

   char const* val = sca->mem;
   if ( move_if_any_char_c( sca, C_IntFormats ) )
   {
      return *val;
   }

   return 'd';
}

static cChars const C_FloatFormats = slice_c_(
   char, 'f', 'e', 'E', 'g', 'G', 'x', 'X'
);

char parse_float_format_type_c( cScanner* sca )
{
   must_exist_c_( sca );

   char const* val = sca->mem;
   if ( move_if_any_char_c( sca, C_FloatFormats ) )
   {
      return *val;
   }

   return 'f';
}

const char* parse_quote_value_c( cScanner* sca )
{
   must_exist_c_( sca );

   if ( sca->space > 0 )
   {
      const char* val = sca->mem;
      if ( *val == 'q' )
      {
         move_scanner_c( sca, 1 );
         return "\'";
      }
      else if ( *val == 'Q' )
      {
         move_scanner_c( sca, 1 );
         return "\"";
      }
   }

   return NULL;
}

bool parse_sign_flag_c( cScanner* sca )
{
   must_exist_c_( sca );

   if ( sca->space > 0 )
   {
      const char* val = sca->mem;
      if ( *val == '+' )
      {
         move_scanner_c( sca, 1 );
         return true;
      }
   }

   return false;
}

bool parse_memory_flag_c( cScanner* sca )
{
   must_exist_c_( sca );

   if ( sca->space > 0 )
   {
      const char* val = sca->mem;
      if ( *val == '0' )
      {
         move_scanner_c( sca, 1 );
         return true;
      }
   }

   return false;
}

int16_t parse_precision_value_c( cScanner* sca )
{
   must_exist_c_( sca );

   if ( sca->space >= 2 ) // at least ".1"
   {
      const char* c = sca->mem;
      if ( *c == '.' )
      {
         move_scanner_c( sca, 1 ); // skip "."

         int16_t val = 0;
         int64_t size = read_int16_c_( sca, &val );
         if ( size >= 0 )
         {
            return val;
         }
         else
         {
            move_scanner_c( sca, -1 ); // return to start position
         }
      }
   }

   return -1;
}

