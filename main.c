#include <stdlib.h>
#include <stdio.h>
#include "mandelbrot.h"

#include <gdk-pixbuf/gdk-pixbuf.h>

int main(int argc, char** argv) {
//   g_type_init();

   //Default Werte festlegen
   double middle_re = -0.75;
   double middle_im = 0.75;
   double range_re = 3.5;
   double range_im = 2;
   unsigned int width = 1920;
   unsigned int height = 1080;
   int max_iteration = 100;

   GdkPixbuf* pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8,
      width, height);
   int n_channels = gdk_pixbuf_get_n_channels(pixbuf);
   int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
   guchar* pixels = gdk_pixbuf_get_pixels(pixbuf);

   for (unsigned int x = 0; x < width; ++x) {
      for (unsigned int y = 0; y < height; ++y) {
	      //Realteil und Imaginärteil des Pixels bestimmen
		double x_percentage = (double)x / (double)width;
		double y_percentage = (double)y / (double)height;
		double c_real = x_percentage * range_re + middle_re - range_re/2;
		double c_imag = y_percentage * range_im + middle_im - range_re/2;
		
	 guchar* pp = pixels + y * rowstride + x * n_channels;
	 int m =  mandelbrot(c_real, c_imag, max_iteration);
	 //pp[0] = 0; /* red */
	 pp[1] = 155.0 * m; /* green */
	 //pp[2] = 0; /* blue */
	// printf("%d",m); 
	
      }
   }
   gdk_pixbuf_save (pixbuf, "mandelbrot.jpg", "jpeg",
      NULL, "quality", "100", NULL);
}
