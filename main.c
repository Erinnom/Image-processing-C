/*
Objective : load image, edit image and save edited image.
*/


#include <stdio.h>
#include "ti.h"
int main(int argc, char **argv){
    // Tests
    char * file_name = "luffy2.png";
    union image image1;
    load_bmp_image(file_name,&image1);

    printf("Height %d\n",image1.png.header.height);
    printf("Width %d\n",image1.png.header.width);

    for (int i = 0;i < 200;i++){
        if (i % 20 == 19){
            printf(" %3d\n",image1.raw[i]);
        }else {
            printf(" %3d",image1.raw[i]);
        }
    }
    // int k = 0;
    // printf("k %2x\n",&k);
    printf("data %2x <- %2x\n",&image1.raw,image1.raw[0]);
    printf("Signature %2x <- %8s\n",&image1.png.header.signature,image1.png.header.signature);
    printf("File size %2x <- %2x\n",&image1.png.header.length,image1.png.header.length);
    printf("Type %2x <- %2s\n",&image1.png.header.type,image1.png.header.type);
    printf("Width %2x <- %2d\n",&image1.png.header.width,image1.png.header.width>>24);
    printf("Height %2x <- %2d\n",&image1.png.header.height,image1.png.header.height>>24);





}
