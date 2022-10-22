#include "clingo/lang/CObject.h"

/*******************************************************************************

*******************************************************************************/

static cObjectInfo* shift_to_info( CObject* obj )
{
   return obj - sizeof( cObjectInfo );
}

static CObject* shift_to_object( cObjectInfo *info )
{
   return info + 1;
}

/*******************************************************************************

*******************************************************************************/

CObject* new_object_c( int64_t size, cMeta const meta[static 1] )
{
   cObjectInfo const info = default_object_info_c_( meta );
   return alloc_object_c( size, &info );
}

CObject* alloc_object_c( int64_t size, cObjectInfo const info[static 1] )
{
   must_be_positive_c_( size );
   
   cObjectInfo* objInfo = alloc_c( sizeof_c_( cObjectInfo ) + size );
   if ( not objInfo )
   {
      return NULL;
   }

   *objInfo = *info;
   return shift_to_object( objInfo );
}

CObject* let_object_c( void* mem, cMeta const meta[static 1] )
{
   return init_object_c( mem, &object_info_c_( meta, c_Cleanup ) );
}

CObject* init_object_c( void* mem, cObjectInfo const info[static 1] )
{
   cObjectInfo* objInfo = mem;
   *objInfo = *info;
   return shift_to_object( objInfo );
}

uint32_t references_c( CObject const* obj )
{
   must_exist_c_( obj );

   cObjectInfo const* info = get_object_info_c( obj );
   return info->refs;
}

void release_all_c( int n, ... )
{
   va_list list;

   va_start( list, n );

   for ( int i = 0; i < n; ++i )
   {
      CObject* val = va_arg( list, CObject* );
      release_c( val );
   }

   va_end( list );
}

CObject* release_c( CObject* obj )
{
   if( obj )
   {
      cObjectInfo* info = shift_to_info( obj );
      if ( info->refs > 0 )
      {
         info->refs -= 1;
      }
      if ( info->refs == 0 )
      {
         if ( has_c_( info->config, c_Cleanup ) and
              info->meta->cleanup )
         {
            info->meta->cleanup( obj );
         }
         if ( has_c_( info->config, c_Release ) )
         {
            free( info );
            return NULL;
         }
      }
   }

   return obj;
}

CObject* retain_c( CObject* obj )
{
   if ( obj )
   {
      cObjectInfo* info = shift_to_info( obj );
      info->refs += 1;
   }

   return obj;
}

CObject* touch_c( CObject* obj )
{
   must_exist_c_( obj );

   return release_c( retain_c( obj ) );
}

/*******************************************************************************

*******************************************************************************/

char const* get_object_desc_c( CObject const* obj )
{
   must_exist_c_( obj );

   cObjectInfo const* info = get_object_info_c( obj );
   return info->meta->desc;
}

cObjectInfo const* get_object_info_c( CObject const* obj )
{
   must_exist_c_( obj );

   return obj - sizeof( cObjectInfo );
}

