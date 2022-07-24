#include "clingo/string/CStringBuilder.h"

/*******************************************************************************

*******************************************************************************/

struct CStringBuilder
{
   cRecorder rec;
   int64_t len;
};

static inline void cleanup( void* instance )
{
   CStringBuilder* builder = instance;
   reset_recorder_c( &(builder->rec) );

   if ( builder->rec.mem )
   {
      free( builder->rec.mem );
   }
}

cMeta const C_StringBuilderMeta = {
   .desc = stringify_c_( CStringBuilder ),
   .cleanup = &cleanup
};

/*******************************************************************************
 create
*******************************************************************************/

CStringBuilder* make_string_builder_c( int64_t cap )
{
   must_be_positive_c_( cap );

   cObjectInfo const info = default_object_info_c_( &C_StringBuilderMeta );
   CStringBuilder* result = alloc_object_c_( CStringBuilder, &info );
   if ( result == NULL )
   {
      return NULL;
   }

   if ( not alloc_recorder_mem_c( &(result->rec), cap + 1 ) )
   {
      release_c( result );
      return NULL;
   }
   result->len = 0;

   return result;
}

CStringBuilder* new_string_builder_c()
{
   return make_string_builder_c( 256 );
}

/*******************************************************************************
 manage
*******************************************************************************/

void reset_string_builder_c( CStringBuilder* builder )
{
   must_exist_c_( builder );

   if ( recorder_cap_c( &(builder->rec) ) == 0 ) return;

   reset_recorder_c( &(builder->rec) );
   builder->len = 0;
   {
      char* tmp = builder->rec.mem;
      *tmp = '\0';
   }
}

bool resize_string_builder_c( CStringBuilder* builder, int64_t cap )
{
   must_exist_c_( builder );

   if ( cap < builder->rec.pos + 1 )
   {
      return false;
   }

   if ( not realloc_recorder_mem_c( &(builder->rec), cap + 1 ) )
   {
      return false;
   }

   return true;
}

int64_t string_builder_byte_length_c( CStringBuilder const* builder )
{
   must_exist_c_( builder );

   return builder->rec.pos;
}

int64_t string_builder_cap_c( CStringBuilder const* builder )
{
   must_exist_c_( builder );

   int64_t cap = recorder_cap_c( &(builder->rec) );
   return cap > 0 ? ( cap - 1 ) : 0;
}

int64_t string_builder_length_c( CStringBuilder const* builder )
{
   must_exist_c_( builder );

   return builder->len;
}

int64_t string_builder_space_c( CStringBuilder const* builder )
{
   must_exist_c_( builder );

   return builder->rec.space - 1;
}

/*******************************************************************************
 access
*******************************************************************************/

cChars built_chars_c( CStringBuilder const* builder )
{
   must_exist_c_( builder );

   cRecorder const* rec = &(builder->rec);
   return recorded_chars_c( rec );
}

char const* built_cstr_c( const CStringBuilder* builder )
{
   must_exist_c_( builder );

   cRecorder const* rec = &(builder->rec);
   return recorder_cap_c( rec ) > 0 ? recorded_chars_c( rec ).v :
                                      "";
}

CString* turn_into_string_c( CStringBuilder* builder )
{
   must_exist_c_( builder );

   cRecorder* rec = &(builder->rec);

   if ( not realloc_recorder_mem_c( rec, rec->pos + 1 ) )
   {
      printf( "not able to resize\n" );
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
   builder->len = 0;
   return res;
}

/*******************************************************************************
 append
*******************************************************************************/

static bool append( CStringBuilder* builder, cChars chars, int64_t len )
{
   cRecorder* rec = &(builder->rec);

   if ( is_empty_c_( chars ) )
   {
      return true;
      return builder;
   }

   if ( rec->space < chars.s+1 )
   {
      int64_t oldSize = max_c_( recorder_cap_c( rec ), chars.s );
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

   builder->len = len;

   return true;
}

bool append_char_c( CStringBuilder* builder, char c )
{
   must_exist_c_( builder );

   return append( builder, chars_c( 1, &c ), 1 );
}

bool append_chars_c( CStringBuilder* builder, cChars chars )
{
   must_exist_c_( builder );

   if ( is_empty_c_( chars ) )
   {
      return true;
   }

   int64_t const len = count_runes_c( chars );
   if ( len == 0 )
   {
      return false;
   }

   return append( builder, chars, len );
}

extern inline
bool append_cstr_c( CStringBuilder* builder, char const cstr[static 1] );

extern inline
bool append_recorded_c( CStringBuilder* builder, cRecorder rec[static 1] );

bool append_rune_c( CStringBuilder* builder, cRune rune )
{
   must_exist_c_( builder );

   if ( not rune_is_valid_c( rune ) )
   {
      return false;
   }

   cChars cs = chars_c( rune_size_c( rune ), rune.c );
   return append( builder, cs, 1 );
}

bool append_string_c( CStringBuilder* builder, CString const* str )
{
   must_exist_c_( builder );
   must_exist_c_( str );

   return append( builder, scs_c( str ), string_length_c( str ) );
}

