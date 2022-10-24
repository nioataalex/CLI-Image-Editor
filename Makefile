#Copyright Nioata Alexandra 312CAa 2021-2022


build: image_editor

image_editor: apply_filters.c crop_image.c image_editor.c load_image.c rotate_image.c save_image.c select_image.c
	gcc -Wall -Wextra apply_filters.c crop_image.c image_editor.c load_image.c rotate_image.c save_image.c select_image.c -lm -o image_editor
	
clean:
	rm -rf image_editor
