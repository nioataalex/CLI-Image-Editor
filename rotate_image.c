#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "load_image.h"
#include "select_image.h"

void rotate_full_image_gray(photo *image)
{
	double **copy = aloc_matrix(image->width, image->height);
	for (int i = 0; i < image->width; i++)
		for (int j = 0; j < image->height; j++)
			copy[i][j] = image->gray[j][image->width - i - 1];
	free_matrix(image->gray, image->height);
	swap_values(&image->height, &image->width);
	image->gray = aloc_matrix(image->height, image->width);
	for (int i = 0; i < image->height; i++)
		for (int j = 0; j < image->width; j++)
			image->gray[i][j] = copy[i][j];
	swap_values(&image->x2, &image->y2);
	free_matrix(copy, image->height);
}

void rotate_full_image_color(photo *image)
{
	double **copy_r, **copy_b, **copy_g;
	copy_r = aloc_matrix(image->width, image->height);
	copy_g = aloc_matrix(image->width, image->height);
	copy_b = aloc_matrix(image->width, image->height);
	for (int i = 0; i < image->width; i++)
		for (int j = 0; j < image->height; j++) {
			copy_r[i][j] = image->red[j][image->width - i - 1];
			copy_g[i][j] = image->green[j][image->width - i - 1];
			copy_b[i][j] = image->blue[j][image->width - i - 1];
		}
	free_matrix(image->red, image->height);
	free_matrix(image->green, image->height);
	free_matrix(image->blue, image->height);
	swap_values(&image->height, &image->width);
	image->red = aloc_matrix(image->height, image->width);
	image->green = aloc_matrix(image->height, image->width);
	image->blue = aloc_matrix(image->height, image->width);
	for (int i = 0; i < image->height; i++)
		for (int j = 0; j < image->width; j++) {
			image->red[i][j] = copy_r[i][j];
			image->green[i][j] = copy_g[i][j];
			image->blue[i][j] = copy_b[i][j];
		}
	swap_values(&image->x2, &image->y2);
	free_matrix(copy_r, image->height);
	free_matrix(copy_b, image->height);
	free_matrix(copy_g, image->height);
}

void rotate_gray(photo *image)
{
	double **copy;
	copy = aloc_matrix(image->height, image->width);
	for (int i = 0; i < image->height; i++)
		for (int j = 0; j < image->width; j++)
			copy[i][j] = image->gray[i][j];
	int x = image->x1;
	int y = image->y1;
	for (int i = image->x2 - 1; i >= image->x1; i--) {
		x = image->x1;
		for (int j = image->y1; j < image->y2; j++) {
			image->gray[y][x] = copy[j][i];
			x++;
		}
		y++;
	}
	free_matrix(copy, image->height);
}

void rotate_color(photo *image)
{
	double **copy_r, **copy_g, **copy_b;
	copy_r = aloc_matrix(image->height, image->width);
	copy_g = aloc_matrix(image->height, image->width);
	copy_b = aloc_matrix(image->height, image->width);
	for (int i = 0; i < image->height; i++)
		for (int j = 0; j < image->width; j++) {
			copy_r[i][j] = image->red[i][j];
			copy_g[i][j] = image->green[i][j];
			copy_b[i][j] = image->blue[i][j];
		}
	int x = image->x1;
	int y = image->y1;
	for (int i = image->x2 - 1; i >= image->x1; i--) {
		x = image->x1;
		for (int j = image->y1; j < image->y2; j++) {
			image->red[y][x] = copy_r[j][i];
			image->green[y][x] = copy_g[j][i];
			image->blue[y][x] = copy_b[j][i];
			x++;
		}
		y++;
	}
	free_matrix(copy_r, image->height);
	free_matrix(copy_g, image->height);
	free_matrix(copy_b, image->height);
}

void rotate_90_degrees(photo *image)
{
	if (image->filetype == 2 || image->filetype == 5) {
		if (image->x2 == image->width && image->y2 == image->height &&
			image->x1 == 0 && image->y1 == 0)
			rotate_full_image_gray(image);
		else
			rotate_gray(image);
	} else {
		if (image->x2 == image->width && image->y2 == image->height &&
			image->x1 == 0 && image->y1 == 0)
			rotate_full_image_color(image);
		else
			rotate_color(image);
	}
}

//rotates the images at the required angle
void rotate_image(photo *image)
{
	char *part = strtok(NULL, " ");
	int angle = atoi(part);
	int distance_x, distance_y;
	distance_x = image->x2 - image->x1;
	distance_y = image->y2 - image->y1;
	if (angle % 90 != 0 || angle < -360 || angle > 360) {
		printf("Unsupported rotation angle\n");
	} else if (distance_x != distance_y && image->x2 != image->width &&
				image->y2 != image->height && image->x1 != 0 &&
				image->y1 != 0) {
		printf("The selection must be square\n");
	} else {
		switch (angle) {
		case 90:
			rotate_90_degrees(image);
			rotate_90_degrees(image);
			rotate_90_degrees(image);
			break;
		case -90:
			rotate_90_degrees(image);
			break;
		case 180:
			rotate_90_degrees(image);
			rotate_90_degrees(image);
			break;
		case -180:
			rotate_90_degrees(image);
			rotate_90_degrees(image);
			break;
		case 270:
			rotate_90_degrees(image);
			break;
		case -270:
			rotate_90_degrees(image);
			rotate_90_degrees(image);
			rotate_90_degrees(image);
			break;
		}
		//if the angles are 360, -360
		//0, the image remains the same
		printf("Rotated %d\n", angle);
	}
}
