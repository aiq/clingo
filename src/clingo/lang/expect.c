#include "clingo/lang/expect.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>

#include "clingo/type/cCharsToken.h"
#include "clingo/io/fwrite.h"
#include "clingo/io/write.h"
#include "clingo/io/print.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************

*******************************************************************************/

char const* C_TapDesc = " - ";
char const* C_TapSkip = " # SKIP ";
char const* C_TapTodo = " # TODO ";

static FILE* C_LogFile = NULL;
static int C_Success = 0;
static int C_Failure = 0;
static int64_t C_Indent = 0;

/*******************************************************************************
 private util functions
*******************************************************************************/

static int test_number()
{
  return C_Success + C_Failure;
}

/*******************************************************************************
 public functions
*******************************************************************************/

void init_tap_c( const char name[static 1], FILE* output )
{
   C_LogFile = output;
   C_Success = 0;
   C_Failure = 0;

   cErrorStack* es = &error_stack_c_( 128 );
   if ( not fwriteln_c_( C_LogFile, es, "# {s}", name ) )
   {
      println_c_( "abort at tap init: {e}", es->err );
      exit( finish_tap_c_() );
   }
}

void tap_plan_c( int64_t n )
{
   cErrorStack* es = &error_stack_c_( 128 );
   if ( not fwriteln_c_( C_LogFile, es, "1..{i64}", n ) )
   {
      println_c_( "abort at tap plan: {e}", es->err );
      exit( finish_tap_c_() );
   }
}

static void intl_tap( bool result, int n, va_list list )
{
   cErrorStack* es = &error_stack_c_( 128 );
   if ( result )
   {
      C_Success += 1;
      if ( not fwrite_c_( C_LogFile, es, "ok {i64}", test_number() ) )
      {
         println_c_( "abort at test {i64}: {e}", test_number(), es->err );
         exit( finish_tap_c_() );
      }
      fwriteln_list_c( C_LogFile, es, n, list );
   }
   else
   {
      C_Failure += 1;
      fwrite_c_( C_LogFile, es, "not ok {i64}", test_number() );
      if ( not fwriteln_list_c( C_LogFile, es, n, list ) )
      {
         println_c_( "abort at test {i64}: {e}", test_number(), es->err );
         exit( finish_tap_c_() );
      }
   }
}

bool tap_c( bool result, int n, ... )
{
   va_list list;
   va_start( list, n );
   intl_tap( result, n, list );
   va_end( list );
   return result;
}

void tap_note_c( char const note[static 1] )
{
   cErrorStack* es = &error_stack_c_( 128 );
   cCharsToken tok = cstr_token_c_( note );
   while ( next_line_token_c( &tok ) )
   {
      if ( not fwriteln_c_( C_LogFile, es, "# {cs}", tok.x ) )
      {
         println_c_( "abort at note before {i64}: {e}", test_number()+1, es->err );
         exit( finish_tap_c_() );
      }
   }
}

int finish_tap_c( bool withPlan )
{
   if ( withPlan )
   {
      tap_plan_c( test_number() );
   }

   return C_Failure == 0 ? EXIT_SUCCESS
                         : EXIT_FAILURE;
}

/*******************************************************************************
 block
*******************************************************************************/

static inline bool record_cntrl_yaml_char( cRecorder rec[static 1], char c )
{
   if ( char_is_cntrl_c( c ) )
   {
      if ( c == '\0' )
         return write_cstr_c_( rec, "\\0" );
    
      return write_cstr_c_( rec, "\\x" ) and
             write_byte_c( rec, byte_c_( c ), "x" );
   }

   return record_char_c( rec, c );
}

static inline bool record_escaped_yaml_char( cRecorder rec[static 1], char c )
{
   switch ( c )
   {
      case '\"': return write_cstr_c_( rec, "\\\"" ); // double quotation mark
      case '\\': return write_cstr_c_( rec, "\\\\" ); // backslash
      case '\a': return write_cstr_c_( rec, "\\b" );  // alert
      case '\b': return write_cstr_c_( rec, "\\b" );  // backspace
      case '\f': return write_cstr_c_( rec, "\\f" );  // formfeef
      case '\n': return write_cstr_c_( rec, "\\n" );  // newline
      case '\r': return write_cstr_c_( rec, "\\r" );  // carriage return
      case '\t': return write_cstr_c_( rec, "\\t" );  // horzontal tab
      case '\v': return write_cstr_c_( rec, "\\v" );  // vertical tab
      default: return record_cntrl_yaml_char( rec, c );
   }
}

static inline bool record_yaml_double_quoted( cRecorder rec[static 1],
                                              cChars value )
{
   cRune r;
   iterate_runes_c_( itr, &r, value )
   {
      if ( rune_size_c( r ) > 1 )
      {
         if ( not write_rune_c_( rec, r ) )
            return false;
      }
      else
      {
         if ( not record_escaped_yaml_char( rec, r.c[0] ) )
            return false;
      }  
   }

   return true;
}

static inline bool record_yaml_single_quoted( cRecorder rec[static 1],
                                              cChars value )
{
   cRune r;
   iterate_runes_c_( itr, &r, value )
   {
      if ( rune_size_c( r ) > 1 )
      {
         if ( not write_rune_c_( rec, r ) )
            return false;
      }
      else
      {
         if ( rune_is_c( r, "'" ) and
              not write_cstr_c_( rec, "''" ) )
            return false;

         if ( not write_rune_c_( rec, r ) )
            return false;
      }  
   }

   return true;
}

static inline bool record_yaml_string( cRecorder rec[static 1],
                                       int64_t intend,
                                       cChars value )
{
   bool const hasNewlines = find_char_c( value, '\n' ) != NULL;
   bool const hasSingleQuotes = find_char_c( value, '\'' ) != NULL;
   //bool const hasDoubleQuotes = find_char_c( value, '\"' ) != NULL;
   bool const hasCntrl = find_char_match_c( value, char_is_cntrl_c ) != NULL;

   if ( hasNewlines )
   {
      if ( not write_cstr_c_( rec, "|+" ) )
        return false;

      if ( not record_pad_c( rec, ' ', intend ) )
        return false;

      cCharsToken tok = chars_token_c_( value );
      while ( next_line_token_c( &tok ) )
      {
         if ( not record_char_c( rec, '\n' ) ||
              not record_pad_c( rec, ' ', intend+2 ) ||
              not record_chars_c( rec, tok.x ) )
            return false;
      }
      return true;
   }

   if ( hasCntrl or hasSingleQuotes )
   { 
      return record_char_c( rec, '"' ) and
             record_yaml_double_quoted( rec, value ) and
             record_char_c( rec, '"' );
   }

   return record_char_c( rec, '\'' ) and
          record_yaml_single_quoted( rec, value ) and
          record_char_c( rec, '\'' );
}

bool tap_block_begin_c( void )
{
   C_Indent += 2;
   if ( C_Indent > 2 )
      return true;

   cErrorStack* es = &error_stack_c_( 128 );
   if ( not fwriteln_c_( C_LogFile, es, "  ---" ) )
   {
      println_c_( "abort at block after {i64}: {e}", test_number(), es->err );
      exit( finish_tap_c_() );
   }
   return true;
}

bool tap_block_end_c( void )
{
   C_Indent -= 2;
   if ( C_Indent > 0 )
      return false;

   cErrorStack* es = &error_stack_c_( 128 );
   if ( not fwriteln_c_( C_LogFile, es, "  ..." ) )
   {
      println_c_( "abort at block after {i64}: {e}", test_number(), es->err );
      exit( finish_tap_c_() );
   }
   return false;
}

static inline void yaml_for_entry( cChars k,
                                   cChars v,
                                   int64_t intend )
{
   cRecorder* rec = &dyn_recorder_c_( 4096 );
   if ( rec->mem == NULL )
   {
      exit( finish_tap_c_() );
   }

   bool correctKey = record_pad_c( rec, ' ', C_Indent ) and
                     record_chars_c( rec, k ) and
                     write_cstr_c_( rec, ": " );
   if ( not correctKey )
   {
      exit( finish_tap_c_() );
   }

   if ( not record_yaml_string( rec, C_Indent, v ) )
   {
      exit( finish_tap_c_() );
   }

   cErrorStack* es = &error_stack_c_( 1024 );
   fwriteln_c_( C_LogFile, es, "{rec}", rec );
}

void tap_line_c( char const k[static 1], int n, ... )
{
   cRecorder* rec = &dyn_recorder_c_( 1024 );
   va_list list;
   va_start( list, n );
   if ( not write_list_c( rec, n, list ) )
   {
      cErrorStack* es = &error_stack_c_( 256 );
      push_recorder_error_c( es, rec );
      println_c_( "abort generating block entry {s:q} {i64}: {e}",
                  k, test_number(), es->err );
      exit( finish_tap_c_() );
   }
   va_end( list );

   yaml_for_entry( c_c( k ), recorded_chars_c( rec ), 2 );
   free_recorder_mem_c( rec );
}
