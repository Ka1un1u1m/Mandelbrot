#include <stdlib.h>
#include <stdio.h>
#include "mandelbrot.h"


int mandelbrot(double c_real, double c_imag, int max_iteration){
	double z_real = 0;
	double z_imag = 0;
	int iteration = 0;

	while(iteration < max_iteration){

		double tmp = z_real * z_real - z_imag * z_imag + c_real;
		z_imag = 2 * z_real * z_imag + c_imag;
		z_real = tmp;

		if(z_real * z_real + z_imag * z_imag > 4){
			return 0;
		}
		iteration++;
	}

	return 1;

}
