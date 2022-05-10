#include "clingo/io/file.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 open
*******************************************************************************/

extern inline int open_file_c( FILE** file,
                               cChars chars,
                               char const mode[static 1] );

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

extern inline int ferror_close_c( FILE* file );

int read_binary_file_c( cChars path, cVarBytes bytes[static 1] )
{
   FILE* file = NULL;
   int err = open_file_c( &file, path, "rb" );
   if ( err != 0 ) return err;

   *bytes = (cVarBytes)invalid_slice_c_();

   int64_t size = file_size_c( file );
   if ( size <= 0 )  return ferror_close_c( file );

   *bytes = (cVarBytes)heap_slice_c_( size, cByte );
   if ( bytes->v == NULL )
   {
      fclose( file );
      return ENOMEM;
   } 

   if ( not get_file_bytes_c( file, bytes ) )
   {
      free( bytes->v );
      return ferror_close_c( file );
   }

   return fclose( file );
}

int read_text_file_c( cChars path, cVarChars chars[static 1] )
{
   FILE* file = NULL;
   int err = open_file_c( &file, path, "rb" );
   if ( err != 0 ) return err;

   *chars = (cVarChars)invalid_slice_c_();

   int64_t size = file_size_c( file );
   if ( size <= 0 ) return ferror_close_c( file );

   int64_t allocSize = 0;
   if ( not iadd64_c( size, 1, &allocSize ) )
   {
      fclose( file );
      return ERANGE;
   }

   *chars = (cVarChars)heap_slice_c_( allocSize, char );
   if ( chars->v == NULL )
   {
      fclose( file );
      return ENOMEM;
   }

   chars->s = size;
   if ( not get_file_chars_c( file, chars ) )
   {
      free( chars->v );
      return ferror_close_c( file );
   }

   chars->v[chars->s] = '\0';
   return fclose(file);
}
  
int write_binary_file_c( cChars path, cBytes bytes )
{
   FILE* file = NULL;
   int err = open_file_c( &file, path, "wb" );
   if ( err != 0 ) return err;

   if ( not put_file_bytes_c( file, bytes ) )
   {
      return ferror_close_c( file );

   }

   return fclose( file );
}

int write_text_file_c( cChars path, cChars chars )
{
   FILE* file = NULL;
   int err = open_file_c( &file, path, "wb" );
   if ( err != 0 ) return err;

   if ( not put_file_chars_c( file, chars ) )
   {
      return ferror_close_c( file );

   }

   return fclose( file );
}