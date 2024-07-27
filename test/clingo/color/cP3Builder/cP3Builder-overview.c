#include "clingo/color/cP3Builder.h"
#include "clingo/io/FILE.h"
#include "clingo/io/print.h"
#include "clingo/lang/expect.h"

char const* expP3 = "P3\n"
"5 5\n"
"255\n"
"0 0 0  255 255 255  0 0 255  0 255 0  255 0 0\n"
"255 0 0  0 0 0  255 255 255  0 0 255  0 255 0\n"
"0 255 0  255 0 0  0 0 0  255 255 255  0 0 255\n"
"0 0 255  0 255 0  255 0 0  0 0 0  255 255 255\n"
"255 255 255  0 0 255  0 255 0  255 0 0  0 0 0\n"
"";

#define Black_ rgb24_c_( 0, 0, 0 )
#define Red_ rgb24_c_( 255, 0, 0 )
#define Green_ rgb24_c_( 0, 255, 0 )
#define Blue_ rgb24_c_( 0, 0, 255 )
#define White_ rgb24_c_( 255, 255, 255 )

static cVarRgb24Image create_image( void )
{
   cVarRgb24Image image = heap_var_rgb24_image_c_( 5, 5 );
   require_c_( image.data );

   set_rgb24_pixel_c( image, pixel_c_( 0, 0 ), Black_ );
   set_rgb24_pixel_c( image, pixel_c_( 0, 1 ), Red_ );
   set_rgb24_pixel_c( image, pixel_c_( 0, 2 ), Green_ );
   set_rgb24_pixel_c( image, pixel_c_( 0, 3 ), Blue_ );
   set_rgb24_pixel_c( image, pixel_c_( 0, 4 ), White_ );

   set_rgb24_pixel_c( image, pixel_c_( 1, 0 ), White_ );
   set_rgb24_pixel_c( image, pixel_c_( 1, 1 ), Black_ );
   set_rgb24_pixel_c( image, pixel_c_( 1, 2 ), Red_ );
   set_rgb24_pixel_c( image, pixel_c_( 1, 3 ), Green_ );
   set_rgb24_pixel_c( image, pixel_c_( 1, 4 ), Blue_ );

   set_rgb24_pixel_c( image, pixel_c_( 2, 0 ), Blue_ );
   set_rgb24_pixel_c( image, pixel_c_( 2, 1 ), White_ );
   set_rgb24_pixel_c( image, pixel_c_( 2, 2 ), Black_ );
   set_rgb24_pixel_c( image, pixel_c_( 2, 3 ), Red_ );
   set_rgb24_pixel_c( image, pixel_c_( 2, 4 ), Green_ );

   set_rgb24_pixel_c( image, pixel_c_( 3, 0 ), Green_ );
   set_rgb24_pixel_c( image, pixel_c_( 3, 1 ), Blue_ );
   set_rgb24_pixel_c( image, pixel_c_( 3, 2 ), White_ );
   set_rgb24_pixel_c( image, pixel_c_( 3, 3 ), Black_ );
   set_rgb24_pixel_c( image, pixel_c_( 3, 4 ), Red_ );

   set_rgb24_pixel_c( image, pixel_c_( 4, 0 ), Red_ );
   set_rgb24_pixel_c( image, pixel_c_( 4, 1 ), Green_ );
   set_rgb24_pixel_c( image, pixel_c_( 4, 2 ), Blue_ );
   set_rgb24_pixel_c( image, pixel_c_( 4, 3 ), White_ );
   set_rgb24_pixel_c( image, pixel_c_( 4, 4 ), Black_ );

   return image;
}

int main( void )
{
   init_tap_c_();

   cVarRgb24Image varImage = create_image();
   cRgb24Image image = image_copy_c_( varImage );

   cErrorStack* es = &error_stack_c_( 1024 );

   cP3Builder b;
   init_p3_builder_c( &b, image.w, image.h );
   add_p3_image_c( &b, image );

   expect_at_c_( recorded_is_c( b.rec, expP3 ) );

   cleanup_p3_builder_c( &b );

   write_p3_file_c( c_c( "cP3Creator-overview.ppm" ), image, es );
   free_all_c_( varImage.data );

   return finish_tap_c_();
}
