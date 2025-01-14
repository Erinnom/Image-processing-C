/*
Objective : load image, edit image and save edited image.
*/


#include <stdio.h>
#include "ti.h"
int main(int argc, char **argv){
    // Tests

    // Load bmp image
    char *file_name = "luffy2.bmp";
    union image image;
    load_bmp_image(file_name,&image);
    union image image1;
    load_bmp_image(file_name,&image1);

    // for (int i = 0;i < 200;i++){
    //     if (i % 20 == 19){
    //         printf(" %2x\n",image.raw[i]);
    //     }else {
    //         printf(" %2x",image.raw[i]);
    //     }
    // }
    // int k = 0;
    // printf("k %2x\n",&k);
    // printf("data %2x <- %2x\n",&image.raw,image.raw[0]);
    // printf("Signature %2x <- %2x\n",&image.bmp.header.signature,image.bmp.header.signature);
    // printf("File size %2x <- %02d\n",&image.bmp.header.file_size,image.bmp.header.file_size);
    // printf("Header size %2x <- %02d\n",&image.bmp.header.header_size,image.bmp.header.header_size);
    // printf("Width %2x <- %02d\n",&image.bmp.header.width,image.bmp.header.width);
    // printf("Height %2x <- %02d\n",&image.bmp.header.height,image.bmp.header.height);

}
