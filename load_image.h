typedef struct {
	int x1, y1, x2, y2;
	int width, height;
	double **gray, **red, **green, **blue;
	int filetype, maxvalue;

} photo;

//function that dynamically allocates memory
//for a matrix
double **aloc_matrix(int height, int width);

//frees space from a matrix
//take care of the ponies
void free_matrix(double **matrix, int height);

//reads a line
char *read_input(void);

//loads the image from a ascii file or
//binary file, depends of the type
//of image
void load_image(photo *image, int *load_exist);
