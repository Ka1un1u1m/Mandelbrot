#include <stdlib.h>
#include <stdio.h>
#include "mandelbrot.h"
#include <gdk-pixbuf/gdk-pixbuf.h>

int main(int argc, char** argv) {
	
	//Default Werte festlegen
        double horizontal_d = 3.07;
        double middle_re = -0.75;
        double middle_im = 0;
        unsigned int width = 256;
        unsigned int height = 192;
        int max_iteration = 1000;

	
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-h") == 0){
			height = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i],"-w") == 0){
			width = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], "-m") == 0){
			max_iteration = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], "-d") == 0){
			horizontal_d = atof(argv[i+1]);
		}
		else if(strcmp(argv[i], "-y") == 0){
			middle_im = atof(argv[i+1]);
		}
		else if(strcmp(argv[i], "-x") == 0){
			middle_re = atof(argv[i+1]);
		}
	}

	double range_re = horizontal_d;
	double range_im = horizontal_d;



	//g_type_init verursacht komische warnings deshalb hier auskommentiert	
	// g_type_init();
	
	
	//Dinge passieren 
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

			//mandelbrot() gibt einen wert von 0 bis 255 zurück welcher die Farbintensität beschreibt
			double m =  mandelbrot(c_real, c_imag, max_iteration);

			//Hier werden die Farben bestimmt
			// pp[0] = 0.5 * m; /* red */
			pp[1] = m; /* green */
			// pp[2] = 0.25 * m; /* blue */
			// printf("%d",m); 

		}
	}

	//Bilddatei speichern
	gdk_pixbuf_save (pixbuf, "mandelbrot.jpg", "jpeg",
			NULL, "quality", "100", NULL);
}
