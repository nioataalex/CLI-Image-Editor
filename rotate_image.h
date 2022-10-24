//rotates the image at 90 degrees
//depends on the image type and
//selected coordinates
void rotate_90_degrees(photo *image);

void rotate_image(photo *image);

//rotates the whole image at 90 degrees counterclockwise
//image type P2/P5
void rotate_full_image_gray(photo *image);

//rotates the whole image at 90 degrees counterclockwise
//image type P3/P6
void rotate_full_image_color(photo *image);

//rotates the image with the selected coordinates
//at 90 degrees counterclockwise
//image type P2/P5
void rotate_gray(photo *image);

//rotates the image with the selected coordinates
//at 90 degrees counterclockwise
//image type P3/P6
void rotate_color(photo *image);
