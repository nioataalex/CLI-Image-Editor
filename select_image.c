#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "load_image.h"
#define MAX 1000000

void swap_values(int *x, int *y)
{
	int aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

int check_is_number(char *s)
{
	if (s[0] == '-')
		return 1;
	int size = strlen(s) - 1;
	for (int i = 0; i <= size; i++)
		if (!(s[i] >= '0' && s[i] <= '9'))
			return 0;
	return 1;
}

void select_image(photo *image)
{
	char *part = strtok(NULL, " ");
	if (strcmp(part, "ALL") == 0) {
		image->x1 = 0;
		image->y1 = 0;
		image->x2 = image->width;
		image->y2 = image->height;
		printf("Selected ALL\n");
	} else {
		int x_1 = MAX, y_1 = MAX, x_2 = MAX, y_2 = MAX;
		if (part)
			if (check_is_number(part))
				x_1 = atoi(part);
		part = strtok(NULL, " ");
		if (part)
			if (check_is_number(part))
				y_1 = atoi(part);
		part = strtok(NULL, " ");
		if (part)
			if (check_is_number(part))
				x_2 = atoi(part);
		part = strtok(NULL, " ");
		if (part)
			if (check_is_number(part))
				y_2 = atoi(part);
		if (x_1 > x_2)
			swap_values(&x_1, &x_2);
		if (y_1 > y_2)
			swap_values(&y_1, &y_2);
		if (x_1 == MAX || x_2 == MAX || y_1 == MAX || y_2 == MAX) {
			printf("Invalid command\n");
		} else if (x_1 == x_2 || y_1 == y_2) {
			printf("Invalid set of coordinates\n");
		} else if (x_1 >= 0 && x_2 <= image->width &&
					y_1 >= 0 && y_2 <= image->height) {
			printf("Selected %d %d %d %d\n", x_1, y_1, x_2, y_2);
			image->x1 = x_1;
			image->x2 = x_2;
			image->y1 = y_1;
			image->y2 = y_2;
		} else {
			printf("Invalid set of coordinates\n");
		}
	}
}
