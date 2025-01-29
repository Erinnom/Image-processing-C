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

  unsigned char raw[4 * 1024 * 1024]; // 4Mo
};

struct pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

union pixel2 {
    struct pixel value;
    unsigned char raw[4];
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
Objective : convert coordinates from cartesian to index
Input : x : int : x coordinate
        y : int : y coordinate
Output : int : index
*/
int coord_to_index(int x, int y, union image *image) {
    short padding = (4- (image->bmp.width*image->bmp.bits_per_pixel)%4)%4;
    return image->bmp.offset + 2 + (image->bmp.height - 1 - y)*(image->bmp.width + padding)*image->bmp.bits_per_pixel/8 + x*image->bmp.bits_per_pixel/8;
}

/*
Objective : get pixel value from image
Input : image : union bmp_image * : image
        x : int : x coordinate
        y : int : y coordinate

*/
void get_pixel(union image *image, int x, int y,struct pixel *pixel) {
    unsigned int offset = coord_to_index(x, y,image);
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
    unsigned int offset = coord_to_index(x, y,image);
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
    fwrite((image->raw + 2), 1, image->bmp.file_size, file);
  }
  fclose(file);
};

/*
Objective : Create an empty bmp image
Input : image : union bmp_image * : image
        width : int : width
        height : int : height
        bits_per_pixel : int : bits per pixel
*/
void new_bmp_image(union image *image, unsigned int width, unsigned int height, unsigned int bits_per_pixel) {
    if (!image || width == 0 || height == 0 || bits_per_pixel == 0 || bits_per_pixel % 8 != 0) {
        return; // Handle invalid inputs
    }

    // File header
    image->bmp.signature[0] = 'B';
    image->bmp.signature[1] = 'M';
    image->bmp.file_size = 138 + (width * height * bits_per_pixel) / 8; // 138 = 14 (file header) + 124 (DIB header)
    image->bmp.reserved1 = 0;
    image->bmp.reserved2 = 0;
    image->bmp.offset = 138; // Pixel data starts after headers

    // DIB Header (BITMAPV5HEADER)
    image->bmp.header_size = 124; // BITMAPV5HEADER size
    image->bmp.width = width;
    image->bmp.height = height;
    image->bmp.planes = 1; // Always 1 for BMP
    image->bmp.bits_per_pixel = bits_per_pixel; // e.g., 24 for RGB, 32 for RGBA
    image->bmp.compression = 0; // BI_RGB (no compression)
    image->bmp.image_size = (width * height * bits_per_pixel) / 8; // Image size in bytes
    image->bmp.x_pixels_per_meter = 2835; // Default (72 DPI)
    image->bmp.y_pixels_per_meter = 2835; // Default (72 DPI)
    image->bmp.colors_used = 0; // 0 = use all colors (dependent on bits_per_pixel)
    image->bmp.important_colors = 0; // 0 = all colors are important

    // Color masks (used for BI_BITFIELDS, here default to 0 for BI_RGB)
    image->bmp.red_mask = 0;
    image->bmp.green_mask = 0;
    image->bmp.blue_mask = 0;
    image->bmp.alpha_mask = 0;

    // Color space information
    image->bmp.color_space_type = 0x73524742; // sRGB ("sRGB" in ASCII)
    image->bmp.space_endpoints = 0; // No specific color space endpoints
    image->bmp.gamma_red = 0; // No gamma correction
    image->bmp.gamma_green = 0;
    image->bmp.gamma_blue = 0;

    // ICC Profile information
    image->bmp.intent = 4; // LCS_GM_IMAGES (best appearance for images)
    image->bmp.profile_data = 0; // No embedded ICC profile
    image->bmp.profile_size = 0;
    image->bmp.reserved = 0;
}

#endif
