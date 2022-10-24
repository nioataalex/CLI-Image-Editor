#define NUMBER 3

//applies the required filter:
//blur, sharpen, edge, gaussian_blur;
void apply_image(photo *image);

//clamp function
//if a number is smaller than the minimum, in our case 0
//the number becomes 0
//same situation if the number is bigger than the maximum
//(255)
double clamp_function(double x, double min, double max);

//apply the filter, using one of the 4
//matrixes from filter_values.h
//the pixels are changing
void apply_filter(photo *image, const double kernel[NUMBER][NUMBER]);
