#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "load_image.h"
#define MAXIMUM 100

//function that dynamically allocates memory
//for a matrix
double **aloc_matrix(int height, int width)
{
	double **matrix = (double **)malloc(height * sizeof(double *));
	if (!matrix) {
		printf("malloc failed\n");
		return 0;
	}
	for (int i = 0; i < height; i++) {
		matrix[i] = (double *)malloc(width * sizeof(double));
		if (!matrix[i]) {
			printf("malloc failed\n");
			return 0;
		}
	}
	return matrix;
}

void free_matrix(double **matrix, int height)
{
	for (int i = 0; i < height; i++)
		free(matrix[i]);
	free(matrix);
}

char *read_input(void)
{
	char *command;
	command = malloc(MAXIMUM);
	fgets(command, MAXIMUM, stdin);
	if (command[strlen(command) - 1] == '\n')
		command[strlen(command) - 1] = '\0';
	return command;
}

void load_image(photo *image, int *load_exist)
{
	char *filename = strtok(NULL, " ");
	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Failed to load %s\n", filename);
		*load_exist = 0;
	} else {
		*load_exist = 1;
		char character_filetype, pignore, buff;
		fscanf(file, "%c", &pignore);
		fscanf(file, "%c", &character_filetype);
		image->filetype = character_filetype - '0';
		fscanf(file, "%d", &image->width);
		fscanf(file, "%d", &image->height);
		fscanf(file, "%d", &image->maxvalue);
		fscanf(file, "%c", &buff);
		if (image->filetype == 2) {
			image->gray = aloc_matrix(image->height, image->width);
			for (int i = 0; i < image->height; i++) {
				for (int j = 0; j < image->width; j++) {
					double x;
					fscanf(file, "%lf", &x);
					image->gray[i][j] = x;
				}
			}
			fclose(file);
		} else if (image->filetype == 3) {
			image->red = aloc_matrix(image->height, image->width);
			image->green = aloc_matrix(image->height, image->width);
			image->blue = aloc_matrix(image->height, image->width);
			for (int i = 0; i < image->height; i++) {
				for (int j = 0; j < image->width; j++) {
					double x;
					fscanf(file, "%lf", &x);
					image->red[i][j] = x;
					fscanf(file, "%lf", &x);
					image->green[i][j] = x;
					fscanf(file, "%lf", &x);
					image->blue[i][j] = x;
				}
			}
			fclose(file);
		} else if (image->filetype == 5) {
			fpos_t last_pos;
			fgetpos(file, &last_pos);
			fclose(file);
			FILE *file1 = fopen(filename, "rb");
			fsetpos(file1, &last_pos);
			image->gray = aloc_matrix(image->height, image->width);
			for (int i = 0; i < image->height; i++) {
				for (int j = 0; j < image->width; j++) {
					unsigned char x;
					fread(&x, sizeof(unsigned char), 1, file1);
					image->gray[i][j] = (double)x;
				}
			}
			fclose(file1);
		} else if (image->filetype == 6) {
			fpos_t last_pos;
			fgetpos(file, &last_pos);
			fclose(file);
			FILE *file1 = fopen(filename, "rb");
			fsetpos(file1, &last_pos);
			image->red = aloc_matrix(image->height, image->width);
			image->green = aloc_matrix(image->height, image->width);
			image->blue = aloc_matrix(image->height, image->width);
			unsigned char x, y, z;
			for (int i = 0; i < image->height; i++)
				for (int j = 0; j < image->width; j++) {
					fread(&x, sizeof(unsigned char), 1, file1);
					image->red[i][j] = (double)x;
					fread(&y, sizeof(unsigned char), 1, file1);
					image->green[i][j] = (double)y;
					fread(&z, sizeof(unsigned char), 1, file1);
					image->blue[i][j] = (double)z;
				}
			fclose(file1);
		}
		printf("Loaded %s\n", filename);
	}
}
