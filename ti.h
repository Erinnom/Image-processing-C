#ifndef TI
#define TI

#include <stdio.h>

union image{
    struct {
        struct {
            unsigned short draft;
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
        } header;
        struct {
            unsigned char data;
        } data;
    } bmp;

    struct {

    } png;
    unsigned char raw[1024*1024]; // 1Mo
};


/*
Objective : load bmp image
Input : file_name : char * : file name
        image : union bmp_image * : image
Output : void
*/
void load_bmp_image(char *file_name, union image *image){
    FILE *file = fopen(file_name,"rb");
    if(file == NULL){
        printf("Error : file not found");
    } else {
        fread((image->raw+2),1,sizeof(*image),file);
    }
    fclose(file);
};

#endif
