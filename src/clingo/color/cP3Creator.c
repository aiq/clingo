#include "clingo/color/cP3Creator.h"

#include "clingo/io/write_type.h"
#include "clingo/io/write.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define ReachedEndCode_ 1
#define FileErrorCode_ 2
static inline bool set_error( cP3Creator creator[static 1], int err )
{
   creator->err = err;
   return false;
}

static inline bool pixel_is_before( cPixel a, cPixel b )
{
   return a.x < b.x and a.y < b.y;
}

bool append_p3_pixel_c( cP3Creator creator[static 1], cRgb24 rgb )
{
   if ( not pixel_is_before( creator->itr, creator->end ) )
      return set_error( creator, ReachedEndCode_ );

   cRecorder* rec = &recorder_c_( 64 );

   if ( creator->itr.x == 0 and creator->itr.y == 0 )
   {
      write_c_( rec, "P3\n{i32} {i32}\n255\n", creator->end.x, creator->end.y );
   }

   write_uint8_c_( rec, rgb.red );
   record_char_c( rec, ' ' );
   write_uint8_c_( rec, rgb.green );
   record_char_c( rec, ' ' );
   write_uint8_c_( rec, rgb.blue );

   creator->itr.x += 1;
   if ( creator->itr.x == creator->end.x )
   {
      creator->itr.x = 0;
      creator->itr.y += 1;
      record_char_c( rec, '\n' );
   }
   else
   {
      record_chars_c_( rec, "  " );
   }

   if ( not fput_chars_c( creator->file, recorded_chars_c( rec ) ) )
      return set_error( creator, FileErrorCode_ );

   return true;
}

bool push_p3_creator_error_c( cErrorStack es[static 1],
                              cP3Creator creator[static 1] )
{
   if ( creator->err == ReachedEndCode_ )
   {
      return push_lit_error_c( es, "reached end of P3 image" );
   }
   else if ( creator->err == FileErrorCode_ )
   {
      return push_file_error_c( es, creator->file );
   }

   return push_lit_error_c( es, "unkown error code" );
}