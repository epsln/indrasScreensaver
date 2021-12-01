#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <complex.h>

#include "include/complexMath.h"
#include "include/plot.h"
#include "include/arraysOps.h"
#include "include/treeExploration.h"
#include "include/debugTools.h"
#include "include/easing.h"
#include "include/recipes.h"
#include "include/accidents.h"
#include "include/progressBar.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "vroot.h"

#define ANTIALPOW 4
#define WIDTH  2000 * ANTIALPOW 
#define HEIGHT 2000 * ANTIALPOW
#define BOUNDS 1 
#define RANDBOUNDS 0 + 1 * I 
#define EPSI  0.01 
#define MAXWORD 10 
#define LINE 1 
#define BITWISE 1
#define DEBUG 0


int main(){
	time_t pt;
	srand((unsigned) time(&pt));

	double complex ta = 0.;
	double complex tb = 0.;

	XColor blackx, blacks;
	xStuff x;
	x.dpy = XOpenDisplay(getenv("DISPLAY"));
	x.root = DefaultRootWindow(x.dpy);
	x.g = XCreateGC(x.dpy, x.root, 0, NULL);
	XGetWindowAttributes(x.dpy, x.root, &x.wa);

	XAllocNamedColor(x.dpy, DefaultColormapOfScreen(DefaultScreenOfDisplay(x.dpy)), "black", &blacks, &blackx);

	double complex* gens = (double complex*)calloc(4*2*2, sizeof(double complex));

	image_t img;
	image_t* pImg = &img;

	pImg->w       = x.wa.width;
	pImg->h       = x.wa.height;
	pImg->bounds  = BOUNDS;
	pImg->epsi    = EPSI;
	pImg->line    = LINE;
	pImg->maxword = MAXWORD;
	pImg->antialiasingPow = ANTIALPOW;
	pImg->debug  = DEBUG;
	pImg->bitwise= BITWISE;
	pImg->filename = malloc(256* sizeof(char));

	pImg->pointArr = NULL;
	pImg->bitArray = NULL;

	XSetForeground(x.dpy,x.g,blacks.pixel);
	XFillRectangle(x.dpy, x.root, x.g, 0, 0, x.wa.width, x.wa.height);
	XFlush(x.dpy);
	while(1){
		XSetForeground(x.dpy,x.g,blacks.pixel);
		XFillRectangle(x.dpy, x.root, x.g, 0, 0, x.wa.width, x.wa.height);
		XFlush(x.dpy);

		ta = randomComplex(-2 - 1. * I, 2 + 1 * I);
		tb = randomComplex(-2 - 1. * I, 2 + 1 * I);
		//Use a good ta/tb pair 75% of the time
		if ((float)rand()/(float)RAND_MAX < 0.75){
			if ((float)rand()/(float)RAND_MAX < 0.5){
				grandmaRecipe(ta, 2, gens);
			}
			else{
				double complex p = -ta * tb;
				double complex q = cpow(ta, 2) + cpow(tb, 2) - 2;
				double complex tab = (-p+csqrt(cpow(p, 2) - 4 * q))/2; 
				grandmaSpecialRecipe(ta, tb, tab, gens);
			}
		}
		else{
			grandmaRecipe(ta, 2, gens);
		}

		//Explore depth first combination of generators...
		XFlush(x.dpy);
		computeDepthFirst(gens, pImg, x, 0);

		sleep(10);
	}
	return 0;
}
