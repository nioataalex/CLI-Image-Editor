#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "load_image.h"
#include "save_image.h"
#include "select_image.h"
#include "apply_filters.h"
#include "rotate_image.h"
#include "crop_image.h"
#define MAX 1000

int main(void)
{
	char *command;
	photo image;
	int ok = 0;
	int load_exist = 0;
	while (ok == 0) {
		command = read_input();
		char *part = strtok(command, " ");
		//check what operation should be solved
		if (strcmp(part, "LOAD") == 0) {
			if (load_exist == 1)
				exit_image(&image);
			load_image(&image, &load_exist);
			save_coordinates(&image);
		} else if (strcmp(part, "SELECT") == 0) {
			if (load_exist == 0)
				printf("No image loaded\n");
			else
				select_image(&image);
		} else if (strcmp(part, "ROTATE") == 0) {
			if (load_exist == 0)
				printf("No image loaded\n");
			else
				rotate_image(&image);
		} else if (strcmp(part, "CROP") == 0) {
			if (load_exist == 0)
				printf("No image loaded\n");
			else
				crop_image(&image);
		} else if (strcmp(part, "APPLY") == 0) {
			if (load_exist == 0)
				printf("No image loaded\n");
			else
				apply_image(&image);
		} else if (strcmp(part, "SAVE") == 0) {
			if (load_exist == 0)
				printf("No image loaded\n");
			else
				save_image(&image);
		} else if (strcmp(part, "EXIT") == 0) {
			if (load_exist == 0)
				printf("No image loaded\n");
			else
				exit_image(&image);
			ok = 1;
		} else {
			printf("Invalid command\n");
		}
		//frees the memory from the command that was used before
		free(command);
	}
	return 0;
}
