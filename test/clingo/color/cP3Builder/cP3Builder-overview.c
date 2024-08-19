#include "clingo/color/cP3Builder.h"
#include "clingo/io/FILE.h"
#include "clingo/io/print.h"
#include "clingo/lang/expect.h"

#define Black_ rgb24_c_( 0, 0, 0 )
#define Red_ rgb24_c_( 255, 0, 0 )
#define Green_ rgb24_c_( 0, 255, 0 )
#define Blue_ rgb24_c_( 0, 0, 255 )
#define White_ rgb24_c_( 255, 255, 255 )

static cVarRgb24Image image01( void )
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

char const* exp01 = "P3\n"
"5 5\n"
"255\n"
"0 0 0 255 255 255 0 0 255 0 255 0 255 0 0\n"
"255 0 0 0 0 0 255 255 255 0 0 255 0 255 0\n"
"0 255 0 255 0 0 0 0 0 255 255 255 0 0 255\n"
"0 0 255 0 255 0 255 0 0 0 0 0 255 255 255\n"
"255 255 255 0 0 255 0 255 0 255 0 0 0 0 0\n"
"";

static cVarRgb24Image image02( void )
{
   cVarRgb24Image image = heap_var_rgb24_image_c_( 16, 9 );

   fill_rgb24_rect_c( image, pixel_c_( 0, 0 ), pixel_c_( 15, 8 ), Black_ );
   draw_rgb24_rect_c( image, pixel_c_( 1, 1 ), pixel_c_( 14, 7 ), Blue_ );
   draw_rgb24_line_c( image, pixel_c_( 0, 0 ), pixel_c_( 15, 8 ), Red_ );
   draw_rgb24_line_c( image, pixel_c_( 0, 8 ), pixel_c_( 15, 0 ), Green_ );

   return image;
}

char const* exp02 = "P3\n"
"16 9\n"
"255\n"
"255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 0\n"
"0 0 0 255 0 0 255 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 255 0 0 255 0 0 0 0\n"
"0 0 0 0 0 255 0 0 0 255 0 0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 0 0 255 0 0 0 0 0 0 255 0 0 0\n"
"0 0 0 0 0 255 0 0 0 0 0 0 0 0 0 255 0 0 255 0 0 0 0 0 0 0 0 0 255 0 0 255 0 0 0 0 0 0 0 0 0 0 0 0 255 0 0 0\n"
"0 0 0 0 0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 0 0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 0 0 0\n"
"0 0 0 0 0 255 0 0 0 0 0 0 0 0 0 0 255 0 0 255 0 0 0 0 0 0 0 255 0 0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 255 0 0 0\n"
"0 0 0 0 0 255 0 0 0 0 255 0 0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 0 0 255 0 0 0 0 0 0 0 255 0 0 0\n"
"0 0 0 0 255 0 0 255 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 255 0 0 255 0 0 0 0 0\n"
"0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 0 0\n"
"";

TEMP_SLICE_C_(
   test,
   {
      cVarRgb24Image image;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( image01(), exp01 ),
      t_( image02(), exp02 )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cRgb24Image image = image_copy_c_( t->image );

      cErrorStack* es = &error_stack_c_( 1024 );

      cP3Builder b;
      init_p3_builder_c( &b, image.w, image.h );
      add_p3_image_c( &b, image );
      expect_at_c_( recorded_is_c( b.rec, t->exp ) );
      cleanup_p3_builder_c( &b );

      cRecorder* nameRec = &recorder_c_( 1024 );
      write_c_( nameRec, "cP3Creator-overview-{i:(2>0)}.ppm", i+1 );
      write_p3_file_c( recorded_chars_c( nameRec ), image, es );

      free_all_c_( t->image.data );

   }

   return finish_tap_c_();
}
