#ifndef TI
#define TI

#include <stdio.h>

union image {
  struct bmp {
    unsigned short draft; // add an offset of 2 bytes to avoid byte de-alignment
    unsigned char signature[2];
    unsigned int file_size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bits_per_pixel;
    unsigned int compression;
    unsigned int image_size;
    unsigned int x_pixels_per_meter;
    unsigned int y_pixels_per_meter;
    unsigned int colors_used;
    unsigned int important_colors;
    unsigned int red_mask;
    unsigned int green_mask;
    unsigned int blue_mask;
    unsigned int alpha_mask;
    unsigned int color_space_type;
    unsigned int space_endpoints;
    unsigned int gamma_red;
    unsigned int gamma_green;
    unsigned int gamma_blue;
    unsigned int intent;
    unsigned int profile_data;
    unsigned int profile_size;
    unsigned int reserved;
  } bmp;

  unsigned char raw[2 * 1024 * 1024]; // 1Mo
};

struct pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

/*
Objective : load bmp image
Input : file_name : char * : file name
        image : union bmp_image * : image
Output : void
*/
void load_bmp_image(char *file_name, union image *image) {
  FILE *file = fopen(file_name, "rb");
  if (file == NULL) {
    printf("Error : file not found");
  } else {
    fread((image->raw + 2), 1, sizeof(*image), file);
  }
  fclose(file);
};

/*
Objective : get pixel value from image
Input : image : union bmp_image * : image
        x : int : x coordinate
        y : int : y coordinate

*/
void get_pixel(union image *image, int x, int y,struct pixel *pixel) {
    unsigned int offset = image->bmp.offset+2 + ((image->bmp.height - y - 1)*(image->bmp.width +1)+ x)*image->bmp.bits_per_pixel/8;
    pixel->blue = image->raw[offset];
    pixel->green = image->raw[offset + 1];
    pixel->red = image->raw[offset + 2];
    if (image->bmp.bits_per_pixel == 32) {
        pixel->alpha = image->raw[offset + 3];
    }
}

/*
Objective : set pixel value from image
Input : image : union bmp_image * : image
        x : int : x coordinate
        y : int : y coordinate
        pixel : struct pixel * : pixel
*/
void set_pixel(union image *image, int x, int y,struct pixel *pixel) {
    unsigned int offset = image->bmp.offset+2 + ((image->bmp.height - y - 1)*(image->bmp.width +1)+ x)*image->bmp.bits_per_pixel/8;
    image->raw[offset] = pixel->blue;
    image->raw[offset + 1] = pixel->green;
    image->raw[offset + 2] = pixel->red;
    if (image->bmp.bits_per_pixel == 32) {
        image->raw[offset + 3] = pixel->alpha;
    }
}

/*
Objective : save bmp image
Input : file_name : char * : file name
        image : union bmp_image * : image
*/
void save_bmp_image(char *file_name, union image *image) {
  FILE *file = fopen(file_name, "wb");
  if (file == NULL) {
    printf("Error : file not found");
  } else {
    fwrite((image->raw + 2), 1, sizeof(*image), file);
  }
  fclose(file);
};

#endif
