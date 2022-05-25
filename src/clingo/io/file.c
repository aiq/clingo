#include "clingo/io/file.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************

*******************************************************************************/

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

extern inline int remove_file_c( cChars path );

/*******************************************************************************
 
*******************************************************************************/

int64_t file_size_c( FILE* file )
{
   must_exist_c_( file );

   long pos = ftell( file );
   fseek( file, 0, SEEK_END );
   int64_t res = ftell( file );
   fseek( file, pos, SEEK_SET );
   return res;
}

/*******************************************************************************
 
*******************************************************************************/

bool fread_bytes_c( FILE* file, cVarBytes bytes[static 1] )
{
   must_exist_c_( file );

   if ( is_empty_c_( *bytes ) ) return false;

   size_t size = 0;
   if ( not int64_to_size_c( bytes->s, &size ) ) return false;

   size_t res = fread( bytes->v, 1, size, file );
   if ( res == 0 ) return false;

   return uint64_to_int64_c( res, &bytes->s );
}

bool fread_chars_c( FILE* file, cVarChars chars[static 1] )
{
   must_exist_c_( file );

   if ( is_empty_c_( *chars ) ) return false;

   size_t size = 0;
   if ( not int64_to_size_c( chars->s, &size ) ) return false;

   size_t res = fread( chars->v, 1, size, file );
   if ( res == 0 ) return false;

   return uint64_to_int64_c( res, &chars->s );
}

bool fwrite_bytes_c( FILE* file, cBytes bytes )
{
   must_exist_c_( file );

   if ( is_empty_c_( bytes ) ) return true;

   size_t size = 0;
   if ( not int64_to_size_c( bytes.s, &size ) ) return false;

   size_t res = fwrite( bytes.v, 1, size, file );
   return res == size;
}

bool fwrite_chars_c( FILE* file, cChars chars )
{
   must_exist_c_( file );

   if ( is_empty_c_( chars ) ) return true;

   size_t size = 0;
   if ( not int64_to_size_c( chars.s, &size ) ) return false;

   size_t res = fwrite( chars.v, 1, size, file );
   return res == size;
}

/*******************************************************************************
 
*******************************************************************************/

extern inline int ferror_close_c( FILE* file );

cVarBytes read_binary_file_c( cChars path, cErrorStack es[static 1] )
{
   cVarBytes invalidBytes = invalid_slice_c_();

   FILE* file = open_file_c( path, "rb", es );
   if ( file == NULL ) return invalidBytes;


   int64_t size = file_size_c( file );
   if ( size <= 0 )
   {
      push_file_error_and_close_c( es, file );
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
      push_file_error_and_close_c( es, file );
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

   FILE* file = open_file_c( path, "rb", es );
   if ( file == NULL ) return invalidChars;

   int64_t size = file_size_c( file );
   if ( size <= 0 )
   {
      push_file_error_and_close_c( es, file );
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
      push_file_error_and_close_c( es, file );
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
   FILE* file = open_file_c( path, "wb", es );
   if ( file == NULL ) return false;

   if ( not fwrite_bytes_c( file, bytes ) )
   {
      return push_file_error_and_close_c( es, file );
   }

   return close_file_c( file, es );
}

bool write_text_file_c( cChars path, cChars chars, cErrorStack es[static 1] )
{
   FILE* file = open_file_c( path, "wb", es );
   if ( file == NULL ) return false;

   if ( not fwrite_chars_c( file, chars ) )
   {
      return push_file_error_and_close_c( es, file );
   }

   return close_file_c( file, es );
}

/*******************************************************************************
 error
*******************************************************************************/

bool push_file_error_c( cErrorStack es[static 1], FILE* file )
{
   cFileErrorData d = { .number=ferror( file ) };
   return push_error_c( es, &C_FileError, &d, sizeof_c_( cFileErrorData ) );
}

bool push_file_error_and_close_c( cErrorStack es[static 1], FILE* file )
{
   cFileErrorData d = { .number=ferror( file ) };
   push_error_c( es, &C_FileError, &d, sizeof_c_( cFileErrorData ) );
   close_file_c( file, es );
   return false;
}

bool note_file_error_c( cRecorder rec[static 1], cError const* err )
{
   cFileErrorData const* errd = get_error_data_c( err );
   char* errStr = strerror( errd->number );
   if ( errStr == NULL ) return false;

   return record_chars_c_( rec, errStr );
}