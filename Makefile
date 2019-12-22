
all : main.o mandelbrot.o 
	gcc -std=gnu11 -Wall -o mandelbrot main.o mandelbrot.o `pkg-config --cflags --libs gdk-pixbuf-2.0` 

main.o : main.c
	gcc -std=gnu11 -Wall -c main.c `pkg-config --cflags --libs gdk-pixbuf-2.0`

mandelbrot.o : mandelbrot.c mandelbrot.h
	gcc -std=gnu11 -Wall -c mandelbrot.c


clean : 
	rm -f *.o
	rm -f mandelbrot 
	rm -f *.core
