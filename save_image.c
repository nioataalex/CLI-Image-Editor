#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "load_image.h"

void save_image(photo *image)
{
	char *filename = strtok(NULL, " ");
	FILE *file1 = fopen(filename, "w");
	fprintf(file1, "P");
	char *savetype = strtok(NULL, " ");
	if (!savetype) {
		if (image->filetype == 2)
			image->filetype = 5;
		if (image->filetype == 3)
			image->filetype = 6;
		fprintf(file1, "%d\n", image->filetype);
		fprintf(file1, "%d %d\n", image->width, image->height);
		fprintf(file1, "%d\n", image->maxvalue);
		fclose(file1);
		FILE *file2 = fopen(filename, "ab");
		if (image->filetype == 5) {
			for (int i = 0; i < image->height; i++) {
				for (int j = 0; j < image->width; j++) {
					unsigned char x = round(image->gray[i][j]);
					fwrite(&x, sizeof(unsigned char), 1, file2);
				}
			}
			fclose(file2);
		} else {
			for (int i = 0; i < image->height; i++) {
				for (int j = 0; j < image->width; j++) {
					unsigned char x = round(image->red[i][j]);
					unsigned char y = round(image->green[i][j]);
					unsigned char z = round(image->blue[i][j]);
					fwrite(&x, sizeof(unsigned char), 1, file2);
					fwrite(&y, sizeof(unsigned char), 1, file2);
					fwrite(&z, sizeof(unsigned char), 1, file2);
				}
			}
			fclose(file2);
		}
	} else {
		if (image->filetype == 5)
			image->filetype = 2;
		if (image->filetype == 6)
			image->filetype = 3;
		fprintf(file1, "%d\n", image->filetype);
		fprintf(file1, "%d %d\n", image->width, image->height);
		fprintf(file1, "%d\n", image->maxvalue);
		if (image->filetype == 2) {
			for (int i = 0; i < image->height; i++) {
				for (int j = 0; j < image->width; j++)
					fprintf(file1, "%.0lf ", round(image->gray[i][j]));
				fprintf(file1, "\n");
			}
			fclose(file1);
		} else {
			for (int i = 0; i < image->height; i++) {
				for (int j = 0; j < image->width; j++)
					fprintf(file1, "%.0lf %.0lf %.0lf ",
							round(image->red[i][j]),
							round(image->green[i][j]),
							round(image->blue[i][j]));
				fprintf(file1, "\n");
			}
			fclose(file1);
		}
	}
	printf("Saved %s\n", filename);
}

void exit_image(photo *image)
{
	if (image->filetype == 2 || image->filetype == 5) {
		free_matrix(image->gray, image->height);
	} else {
		free_matrix(image->red, image->height);
		free_matrix(image->green, image->height);
		free_matrix(image->blue, image->height);
	}
}

void save_coordinates(photo *image)
{
	image->x1 = 0;
	image->x2 = image->width;
	image->y1 = 0;
	image->y2 = image->height;
}
