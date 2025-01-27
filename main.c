/*
Objective : load image, edit image and save edited image.
*/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "ti.h"
#include "math.h"


/*
Objective : Turn a color image to a grayscale image
Input : struct image : image
*/
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


/*
Objective : add noise to an image
Input : struct image : image
*/
void noise(union image *image,float weight) {
    srand(time(NULL));
    for (int i = 0; i < image->bmp.width; i++){
        for(int j = 0; j < image->bmp.height; j++){

            struct pixel pixel;
            get_pixel(image,i,j,&pixel);
            pixel.blue = min( pixel.blue+(rand()%0xff)*weight,255);
            pixel.green = min(pixel.green+(rand()%0xff)*weight,255);
            pixel.red = min(pixel.red+(rand()%0xff)*weight,255);
            set_pixel(image,i,j,&pixel);
        }
    }
}



int main(int argc, char **argv){
    // Tests
    union image image1;
    //load_bmp_image("chiffrement.bmp",&image1);
    new_bmp_image(&image1, 300, 200, 8);
    noise(&image1,0.6);
    save_bmp_image("new_image1.bmp", &image1);
}
