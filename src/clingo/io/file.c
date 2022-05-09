#include "clingo/io/file.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 open
*******************************************************************************/

extern inline FILE* open_file_c( cChars chars, char const mode[static 1] );

extern inline bool remove_file_c( cChars path );

/*******************************************************************************
 
*******************************************************************************/

int64_t file_size_c( FILE* file )
{
   must_exist_c_( file );

   int64_t pos = ftell( file );
   fseek( file, 0, SEEK_END );
   int64_t res = ftell( file );
   fseek( file, pos, SEEK_SET );
   return res;
}

/*******************************************************************************
 
*******************************************************************************/

bool get_file_bytes_c( FILE* file, cVarBytes bytes[static 1] )
{
   must_exist_c_( file );

   if ( is_empty_c_( *bytes ) ) return false;

   size_t size = 0;
   if ( not int64_to_size_c( bytes->s, &size ) ) return false;

   size_t res = fread( bytes->v, 1, size, file );
   if ( res == 0 ) return false;

   return uint64_to_int64_c( res, &bytes->s );
}

bool get_file_chars_c( FILE* file, cVarChars chars[static 1] )
{
   must_exist_c_( file );

   if ( is_empty_c_( *chars ) ) return false;

   size_t size = 0;
   if ( not int64_to_size_c( chars->s, &size ) ) return false;

   size_t res = fread( chars->v, 1, size, file );
   if ( res == 0 ) return false;

   return uint64_to_int64_c( res, &chars->s );
}

bool put_file_bytes_c( FILE* file, cBytes bytes )
{
   must_exist_c_( file );

   if ( is_empty_c_( bytes ) ) return true;

   size_t size = 0;
   if ( not int64_to_size_c( bytes.s, &size ) ) return false;

   size_t res = fwrite( bytes.v, 1, size, file );
   return res == size;
}

bool put_file_chars_c( FILE* file, cChars chars )
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

cVarBytes read_binary_file_c( cChars path )
{
   FILE* file = NULL;
   cVarBytes bytes = empty_var_bytes_c();

   once_c_( xyz )
   {
      file = open_file_c( path, "r" );
      if ( file == NULL ) break;

      int64_t size = file_size_c( file );
      if ( size <= 0 ) break;

      bytes = (cVarBytes)heap_slice_c_( size, cByte );
      if ( bytes.v == NULL ) break;

      if ( not get_file_bytes_c( file, &bytes ) ) break;

      fclose( file );
      return bytes;
   }

   if ( file != NULL ) fclose( file );
   if ( bytes.v != NULL ) free( bytes.v );
   bytes.s = -1;
   return bytes;
}

cVarChars read_text_file_c( cChars path )
{
   FILE* file = NULL;
   cVarChars chars = empty_var_chars_c();

   once_c_( xyz )
   {
      file = open_file_c( path, "r" );
      if ( file == NULL ) break;

      int64_t size = file_size_c( file );
      if ( size <= 0 ) break;

      int64_t allocSize = 0;
      if ( not iadd64_c( size, 1, &allocSize ) ) break;

      chars = (cVarChars)heap_slice_c_( allocSize, char );
      if ( chars.v == NULL ) break;

      chars.s = size;
      if ( not get_file_chars_c( file, &chars ) ) break;

      chars.v[chars.s] = '\0';

      fclose(file);
      return chars;
   }

   if ( file != NULL ) fclose( file );
   if ( chars.v != NULL ) free( chars.v );
   chars.s = -1;
   return chars;
}
  
bool write_binary_file_c( cChars path, cBytes bytes )
{
   FILE* file = open_file_c( path, "wb" );
   if ( file == NULL )
   {
      return NULL;
   }

   bool res = put_file_bytes_c( file, bytes );

   fclose( file );
   return res;
}

bool write_text_file_c( cChars path, cChars chars )
{
   FILE* file = open_file_c( path, "w" );
   if ( file == NULL )
   {
      return NULL;
   }

   bool res = put_file_chars_c( file, chars );

   fclose( file );
   return res;
}