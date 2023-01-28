#include "clingo/string/cStringBuilder.h"

/*******************************************************************************
 create
*******************************************************************************/

bool init_string_builder_c( cStringBuilder b[static 1], int64_t cap )
{
   if ( not alloc_recorder_mem_c( &(b->rec), cap + 1 ) )
   {
      return false;
   }
   b->len = 0;

   return b;
}

void cleanup_string_builder_c( cStringBuilder b[static 1] )
{
   reset_recorder_c( &(b->rec) );

   if ( b->rec.mem )
   {
      free( b->rec.mem );
   }
}

/*******************************************************************************
 manage
*******************************************************************************/

void reset_string_builder_c( cStringBuilder b[static 1] )
{
   if ( recorder_cap_c( &(b->rec) ) == 0 ) return;

   reset_recorder_c( &(b->rec) );
   b->len = 0;
   {
      char* tmp = b->rec.mem;
      *tmp = '\0';
   }
}

bool resize_string_builder_c( cStringBuilder b[static 1], int64_t cap )
{
   if ( cap < b->rec.pos + 1 )
   {
      return false;
   }

   if ( not realloc_recorder_mem_c( &(b->rec), cap + 1 ) )
   {
      return false;
   }

   return true;
}

int64_t string_builder_byte_length_c( cStringBuilder const b[static 1] )
{
   return b->rec.pos;
}

int64_t string_builder_cap_c( cStringBuilder const b[static 1] )
{
   int64_t cap = recorder_cap_c( &(b->rec) );
   return cap > 0 ? ( cap - 1 ) : 0;
}

int64_t string_builder_length_c( cStringBuilder const b[static 1] )
{
   return b->len;
}

int64_t string_builder_space_c( cStringBuilder const b[static 1] )
{
   return b->rec.space - 1;
}

/*******************************************************************************
 access
*******************************************************************************/

cChars built_chars_c( cStringBuilder const b[static 1] )
{
   cRecorder const* rec = &(b->rec);
   return recorded_chars_c( rec );
}

char const* built_cstr_c( const cStringBuilder b[static 1] )
{
   cRecorder const* rec = &(b->rec);
   return recorder_cap_c( rec ) > 0 ? recorded_chars_c( rec ).v :
                                      "";
}

CString* turn_into_string_c( cStringBuilder b[static 1] )
{
   cRecorder* rec = &(b->rec);

   if ( not realloc_recorder_mem_c( rec, rec->pos + 1 ) )
   {
      return NULL;
   }

   int64_t oldPos = rec->pos;
   reset_recorder_c( rec );
   char* cstr = rec->mem;
   CString* res = adopt_cstr_c( cstr );
   if ( res == NULL )
   {
      move_recorder_to_c( rec, oldPos );
      return NULL;
   }

   rec->mem = NULL;
   rec->space = 0;
   b->len = 0;
   return res;
}

/*******************************************************************************
 append
*******************************************************************************/

static bool append( cStringBuilder b[static 1], cChars chars, int64_t len )
{
   cRecorder* rec = &(b->rec);

   if ( is_empty_c_( chars ) )
   {
      return true;
   }

   if ( rec->space < chars.s+1 )
   {
      int64_t oldSize = imax64_c( recorder_cap_c( rec ), chars.s );
      int64_t const newSize = oldSize * 2;
      if ( not realloc_recorder_mem_c( rec, newSize ) )
      {
         return false;
      }
   }

   if ( not record_chars_c( rec, chars ) )
   {
      return false;
   }

   {
      char* tmp = rec->mem;
      *tmp = '\0';
   }

   b->len = len;

   return true;
}

bool append_char_c( cStringBuilder b[static 1], char c )
{
   return append( b, (cChars){ 1, &c }, 1 );
}

bool append_chars_c( cStringBuilder b[static 1], cChars chars )
{
   if ( is_empty_c_( chars ) )
   {
      return true;
   }

   int64_t const len = count_runes_c( chars );
   if ( len == 0 )
   {
      return false;
   }

   return append( b, chars, len );
}

extern inline
bool append_cstr_c( cStringBuilder b[static 1], char const cstr[static 1] );

extern inline
bool append_recorded_c( cStringBuilder b[static 1], cRecorder rec[static 1] );

bool append_rune_c( cStringBuilder b[static 1], cRune rune )
{
   if ( not rune_is_valid_c( rune ) )
   {
      return false;
   }

   cChars cs = { rune_size_c( rune ), rune.c };
   return append( b, cs, 1 );
}

bool append_string_c( cStringBuilder b[static 1], CString const* str )
{
   must_exist_c_( str );

   return append( b, scs_c( str ), string_length_c( str ) );
}

