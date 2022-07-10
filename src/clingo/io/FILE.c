#include "clingo/io/FILE.h"

#include <limits.h>

#include "clingo/io/write.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************

*******************************************************************************/

QUOTE_LIT_STR_ERROR_TYPE_C_(
   C_ReadError,
   note_read_error_c,
   "not able to read {s:q}",
   push_read_error_c
)

QUOTE_LIT_STR_ERROR_TYPE_C_(
   C_InvalidValueError,
   note_invalid_value_error_c,
   "invalid {s:q} value",
   push_invalid_value_error_c
)

SINGLE_ERROR_TYPE_C_( C_Eof, note_eof_c, "EOF" )

SINGLE_ERROR_TYPE_C_(
   C_UnexpectedEof,
   note_unexpected_eof_c,
   "unexpected EOF"
);

static bool note_file_error_c( cRecorder rec[static 1], cError const* err )
{
   cFileErrorData const* errd = get_error_data_c( err );
   char* errStr = strerror( errd->number );
   if ( errStr == NULL ) return false;

   return record_chars_c_( rec, errStr );
}
cErrorType const C_FileError = {
   .desc = stringify_c_( C_FileError ),
   .note = &note_file_error_c
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 open
*******************************************************************************/

bool close_file_c( FILE* file, cErrorStack es[static 1] )
{
   int errNum = fclose( file );
   if ( errNum != 0 )
   {
      push_errno_error_c( es, errNum );
      return false;
   }
   return true;
}

extern inline FILE* open_file_c( cChars chars,
                                 char const mode[static 1],
                                 cErrorStack es[static 1] );

extern inline bool remove_file_c( cChars path, cErrorStack es[static 1] );

extern inline FILE* ropen_file_c( cChars path, cErrorStack es[static 1] );

extern inline FILE* wopen_file_c( cChars path, cErrorStack es[static 1] );

/*******************************************************************************
 
*******************************************************************************/

int64_t file_size_c( FILE* file )
{
   must_exist_c_( file );

   long pos = ftell( file );
   if ( fseek( file, 0, SEEK_END ) != 0 ) return -1;

   int64_t res = ftell( file );
   
   if ( fseek( file, pos, SEEK_SET ) != 0 ) return -1;

   return res;
}

/*******************************************************************************
 
*******************************************************************************/

bool fread_bytes_c( FILE* file, cVarBytes buf[static 1] )
{
   must_exist_c_( file );

   if ( is_empty_c_( *buf ) ) return false;

   size_t size = 0;
   must_be_c_( int64_to_size_c( buf->s, &size ) );

   size_t res = fread( buf->v, 1, size, file );
   if ( res == 0 ) return false;

   must_be_c_( uint64_to_int64_c( res, &(buf->s) ) );
   if ( size != res and ferror( file ) != 0 ) return false;

   return true;
}

bool fread_chars_c( FILE* file, cVarChars buf[static 1] )
{
   must_exist_c_( file );

   if ( is_empty_c_( *buf ) ) return false;

   size_t size = 0;
   must_be_c_( int64_to_size_c( buf->s, &size ) );

   size_t res = fread( buf->v, 1, size, file );
   if ( res == 0 ) return false;

   must_be_c_( uint64_to_int64_c( res, &(buf->s) ) );
   if ( size != res and ferror( file ) != 0 ) return false;

   return true;
}

bool fread_line_c( FILE* file,
                   int32_t n,
                   cVarChars buf[static 1],
                   bool fin[static 1] )
{
   must_exist_c_( file );
   must_be_in_range_c_( 4, n, INT_MAX );
   *fin = false;

   if ( feof( file ) != 0 ) return false;
 
   char* str = fgets( buf->v, (int)n, file );
   if ( str == NULL )
   {
      if ( feof( file ) != 0 )
      {
         buf->s = 0;
         buf->v[0] = '\0';
         *fin = true;
         return true;
      }
      return false;
   }

   uint64_to_int64_c( strlen( str ), &buf->s );
   if ( last_c_( *buf ) == '\n' )
   {
      *fin = true;
      --buf->s;
   }

   return true;
}

/*******************************************************************************
 
*******************************************************************************/

bool fwrite_bytes_c( FILE* file, cBytes bytes )
{
   must_exist_c_( file );

   if ( is_empty_c_( bytes ) ) return true;

   size_t size = 0;
   must_be_c_( int64_to_size_c( bytes.s, &size ) );

   size_t res = fwrite( bytes.v, 1, size, file );
   return res == size;
}

bool fwrite_chars_c( FILE* file, cChars chars )
{
   must_exist_c_( file );

   if ( is_empty_c_( chars ) ) return true;

   size_t size = 0;
   must_be_c_( int64_to_size_c( chars.s, &size ) );

   size_t res = fwrite( chars.v, 1, size, file );
   return res == size;
}

/*******************************************************************************
 
*******************************************************************************/

static inline bool push_file_error_and_close( cErrorStack es[static 1],
                                              FILE* file )
{
   push_file_error_c( es, file );
   close_file_c( file, es );
   return false;
}

cVarBytes read_binary_file_c( cChars path, cErrorStack es[static 1] )
{
   cVarBytes invalidBytes = invalid_slice_c_();

   FILE* file = ropen_file_c( path, es );
   if ( file == NULL ) return invalidBytes;


   int64_t size = file_size_c( file );
   if ( size <= 0 )
   {
      push_file_error_and_close( es, file );
      return invalidBytes;
   }

   cVarBytes bytes = heap_slice_c_( size, cByte );
   if ( bytes.v == NULL )
   {
      close_file_c( file, es );
      push_errno_error_c( es, ENOMEM );
      return invalidBytes;
   }

   if ( not fread_bytes_c( file, &bytes ) )
   {
      free( bytes.v );
      push_file_error_and_close( es, file );
      return invalidBytes;
   }

   if ( not close_file_c( file, es ) )
   {
      free( bytes.v );
      return invalidBytes;
   }
   return bytes;
}

cVarChars read_text_file_c( cChars path, cErrorStack es[static 1] )
{
   cVarChars invalidChars = invalid_slice_c_();

   FILE* file = ropen_file_c( path, es );
   if ( file == NULL ) return invalidChars;

   int64_t size = file_size_c( file );
   if ( size <= 0 )
   {
      push_file_error_and_close( es, file );
      return invalidChars;
   }

   int64_t allocSize = 0;
   if ( not iadd64_c( size, 1, &allocSize ) )
   {
      push_errno_error_c( es, ERANGE );
      close_file_c( file, es );
      return invalidChars;
   }

   cVarChars chars = heap_slice_c_( allocSize, char );
   if ( chars.v == NULL )
   {
      push_errno_error_c( es, ENOMEM );
      close_file_c( file, es );
      return invalidChars;
   }

   chars.s = size;
   if ( not fread_chars_c( file, &chars ) )
   {
      free( chars.v );
      push_file_error_and_close( es, file );
      return invalidChars;
   }

   chars.v[chars.s] = '\0';
   if ( not close_file_c( file, es ) )
   {
      free( chars.v);
      return invalidChars;
   }
   return chars;
}
  
bool write_binary_file_c( cChars path, cBytes bytes, cErrorStack es[static 1] )
{
   FILE* file = wopen_file_c( path, es );
   if ( file == NULL ) return false;

   if ( not fwrite_bytes_c( file, bytes ) )
   {
      return push_file_error_and_close( es, file );
   }

   return close_file_c( file, es );
}

bool write_text_file_c( cChars path, cChars chars, cErrorStack es[static 1] )
{
   FILE* file = wopen_file_c( path, es );
   if ( file == NULL ) return false;

   if ( not fwrite_chars_c( file, chars ) )
   {
      return push_file_error_and_close( es, file );
   }

   return close_file_c( file, es );
}

/*******************************************************************************
 error
*******************************************************************************/

bool push_file_error_c( cErrorStack es[static 1], FILE* file )
{
   if ( ferror( file ) != 0 )
   {
      cFileErrorData d = { .number=ferror( file ) };
      return push_error_c( es, &C_FileError, &d, sizeof_c_( cFileErrorData ) );
   }
   else if ( feof( file ) != 0 )
   {
      return push_error_c_( es, &C_Eof );
   }
   return false;
}
