#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "load_image.h"

void crop_image(photo *image)
{
	int new_height = image->y2 - image->y1;
	int new_width = image->x2 - image->x1;
	if (image->filetype == 2 || image->filetype == 5) {
		double **new_gray = aloc_matrix(new_height, new_width);
		for (int i = image->y1, i1 = 0; i < image->y2; i++, i1++)
			for (int j = image->x1, j1 = 0; j < image->x2; j++, j1++)
				new_gray[i1][j1] = image->gray[i][j];
		free_matrix(image->gray, image->height);
		image->gray = new_gray;
	} else {
		double **new_red = aloc_matrix(new_height, new_width);
		double **new_green = aloc_matrix(new_height, new_width);
		double **new_blue = aloc_matrix(new_height, new_width);
		for (int i = image->y1, i1 = 0; i < image->y2; i++, i1++) {
			for (int j = image->x1, j1 = 0; j < image->x2; j++, j1++) {
				new_red[i1][j1] = image->red[i][j];
				new_green[i1][j1] = image->green[i][j];
				new_blue[i1][j1] = image->blue[i][j];
			}
		}
		free_matrix(image->red, image->height);
		free_matrix(image->green, image->height);
		free_matrix(image->blue, image->height);
		image->red = new_red;
		image->green = new_green;
		image->blue = new_blue;
	}
	image->height = new_height;
	image->width = new_width;
	image->x1 = 0;
	image->y1 = 0;
	image->x2 = image->width;
	image->y2 = image->height;
	printf("Image cropped\n");
}
