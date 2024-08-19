#include "clingo/color/cP3Builder.h"

#include "clingo/io/write_type.h"
#include "clingo/io/write.h"
#include "clingo/lang/math.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

bool init_p3_builder_c( cP3Builder b[static 1], int32_t w, int32_t h )
{
   if ( w < 1 and h < 1 )
   {
      return false;
   }
   int64_t cap = w * h;
   if ( not imul64_c( cap, 12, &cap ) )
   {
      return false;
   }
   b->ownRec = dyn_recorder_c_( cap );
   if ( b->ownRec.mem == NULL )
   {
      return false;
   }
   b->rec = &b->ownRec;
   b->end = pixel_c_( w, h );
   b->itr = pixel_c_( 0, 0 );
   b->err = 0;
   return true;
}

bool init_p3_builder_shell_c( cP3Builder b[static 1],
                              cRecorder rec[static 1] ,
                              int32_t w,
                              int32_t h )
{
   if ( w < 1 and h < 1 )
   {
      return false;
   }
   b->rec = rec;
   b->end = pixel_c_( w, h );
   b->itr = pixel_c_( 0, 0 );
   b->err = 0;
   return true;
}

void cleanup_p3_builder_c( cP3Builder b[static 1] )
{
   if ( &b->ownRec == b->rec )
   {
      free_recorder_mem_c( b->rec );
   }
}

/*******************************************************************************

*******************************************************************************/

bool add_p3_image_c( cP3Builder b[static 1], cRgb24Image image )
{
   for_each_pixel_c_( x, y, image )
   {
      cRgb24 rgb = get_rgb24_pixel_c( image, pixel_c_( x, y ) );
      if ( not add_p3_pixel_c( b, rgb ) )
      {
         return false;
      }
   }
   return true;
}

#define ReachedEndCode_ 1
#define RecorderError_ 2
static inline bool set_error( cP3Builder b[static 1], int err )
{
   b->err = err;
   return false;
}

static inline bool pixel_is_before( cPixel a, cPixel b )
{
   return a.x < b.x and a.y < b.y;
}

bool add_p3_pixel_c( cP3Builder b[static 1], cRgb24 rgb )
{
   if ( not pixel_is_before( b->itr, b->end ) )
      return set_error( b, ReachedEndCode_ );

   cRecorder* rec = &recorder_c_( 64 );

   if ( b->itr.x == 0 and b->itr.y == 0 )
   {
      write_c_( rec, "P3\n{i32} {i32}\n255\n", b->end.x, b->end.y );
   }

   write_uint8_c_( rec, rgb.red );
   record_char_c( rec, ' ' );
   write_uint8_c_( rec, rgb.green );
   record_char_c( rec, ' ' );
   write_uint8_c_( rec, rgb.blue );

   b->itr.x += 1;
   if ( b->itr.x == b->end.x )
   {
      b->itr.x = 0;
      b->itr.y += 1;
      record_char_c( rec, '\n' );
   }
   else
   {
      record_chars_c_( rec, " " );
   }

   if ( not record_chars_c( b->rec, recorded_chars_c( rec ) ) )
      return set_error( b, RecorderError_ );

   return true;
}

/*******************************************************************************

*******************************************************************************/

bool push_p3_builder_error_c( cErrorStack es[static 1],
                              cP3Builder b[static 1] )
{
   if ( b->err == ReachedEndCode_ )
   {
      return push_lit_error_c( es, "reached end of P3 image" );
   }
   else if ( b->err == RecorderError_ )
   {
      return push_recorder_error_c( es, b->rec );
   }

   return push_lit_error_c( es, "unkown error code" );
}

/*******************************************************************************

*******************************************************************************/

bool write_p3_file_c( cChars path, cRgb24Image image, cErrorStack es[static 1] )
{
   cP3Builder b;
   if ( not init_p3_builder_c( &b, image.w, image.h ) )
   {
      return push_lit_error_c( es, "not able able to init cP3Builder" );
   }

   if ( not add_p3_image_c( &b, image ) )
   {
      return push_p3_builder_error_c( es, &b );
   }

   bool res = write_text_file_c( path, recorded_chars_c( b.rec ), es );
   cleanup_p3_builder_c( &b );
   return res;
}