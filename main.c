/*
Objective : load image, edit image and save edited image.
*/

#include <stdio.h>
#include "ti.h"

void grayscale(union image *image) {
    for (int i = 0; i < image->bmp.width; i++){
        for(int j = 0; j < image->bmp.height; j++){
            struct pixel pixel;
            get_pixel(image,i,j,&pixel);
            pixel.blue = (pixel.blue + pixel.green + pixel.red)/3;
            pixel.green = pixel.blue;
            pixel.red = pixel.blue;
            set_pixel(image,i,j,&pixel);
        }
    }
}

int main(int argc, char **argv){
    // Tests
    char * file_name = "luffy2.bmp";
    union image image1;
    load_bmp_image(file_name,&image1);
    grayscale(&image1);
    save_bmp_image("luffy2-gray.bmp",&image1);
}
