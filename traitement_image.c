#include "mem.c"
#include <stdio.h>

struct pixel{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char s;
};

struct image{
    unsigned int *data;
    unsigned long int width;
    unsigned long int height;
    unsigned long int size;
    unsigned long int bits_per_pixel;
    unsigned long int offset;
};

/*
Objective : Load image
Input : char * file_name
Output : image
*/
struct image * load_image(char * file_name){
    // Load file
    FILE * file = fopen(file_name,"rb");

    // Check if file correctly loaded
    if (file == 0) {
        printf("L'image n'a pas put être chargée");
        return 0;
    }

    // Check if image is a BMP image
    char b = fgetc(file);
    char m = fgetc(file);

    if (b != *"B" || m != *"M"){
        printf("Type BMP attendu");
        return 0;
    }

    // Get file size size

    unsigned long int size = 0;
    unsigned long int s[4];

    for (int i = 0; i < 4; i++){
        s[i] = fgetc(file);
        size += s[i] << (8*i);
    }


    // Load image in variable
    struct image *image = malloc(sizeof(struct image));
    image->data = malloc(sizeof(int) * size);
    image->size = size;
    image->data[0] = b & 0xff;
    image->data[1] = m & 0xff;
    for (int i = 0; i<4;i++){
        image->data[i+2] = s[i] & 0xff;
    }
    for (int i = 6;i < size;i++){
        image->data[i] = fgetc(file) & 0xff;
    }

    // Get image width
    for (int i = 0; i<4;i++){
        image->width += image->data[i+18] << (8*i);
    }

    // Get image height
    for (int i = 0; i<4;i++){
        image->height += image->data[i+22] << (8*i);
    }

    // Get bits per pixel number
    for (int i = 0; i<2;i++){
        image->bits_per_pixel += image->data[i+28] << (8*i);
    }

    // Get offset
    for (int i = 0; i<4;i++){
        image->offset += image->data[i+10] << (8*i);
    }
    return image;
}


/*
Objective : Get pixel value
Input : - struct image
        - long int x
        - long int y
Output : struct pixel
*/
struct pixel * get_pixel(struct image *image,unsigned long int x,unsigned long int y){
    // Create a pixel
    struct pixel *p = malloc(sizeof(struct pixel));
    unsigned long int c = y*(image->bits_per_pixel/8) + (image->width - x - 1)*(image->bits_per_pixel/8)*image->height;
    unsigned long int b = image->data[c+image->offset+0];
    unsigned long int g = image->data[c+image->offset+1];
    unsigned long int r = image->data[c+image->offset+2];
    p->b = b;
    p->g = g;
    p->r = r;
    return p;
}

/*
Objective : Set pixel color
Input : - struct image
        - long int x
        - long int y
        - struct pixel
*/
void set_pixel(struct image *image,unsigned long int x,unsigned long int y, struct pixel *p){
    unsigned long int c = y*(image->bits_per_pixel/8) + (image->width - x - 1)*(image->bits_per_pixel/8)*image->height;
    image->data[c + image->offset+0] = p->b & 0xff;
    image->data[c + image->offset+1] = p->g & 0xff;
    image->data[c + image->offset+2] = p->r & 0xff;
}


/*
Objective : Save image in a file
Input : - struct image
        - char * file_name
*/
void save_image(struct image * image, char * file_name){
    // Create a file
    FILE * file = fopen(file_name,"wb");

    // Write in the file
    for (int i = 0; i < image->size;i++){
        fputc(image->data[i] & 0xff,file);
    }
}

/*
Objective : create a new image
Input : - long int width
        - long int height
Output : struct image
*/
struct image  * new_image(unsigned long int w, unsigned long int h){
    struct image *image = malloc(sizeof(struct image));
    image->width = w;
    image->height = h;
    image->size = 138 + w*h*3;
    image->data = malloc(sizeof(int) * image->size);
    image->data[0] = 'B';
    image->data[1] = 'M';
    image->data[10] = 138;

    // define size metadata
    for (int i = 0; i < 4; i++){
        image->data[i+2] = image->size >> (8*i) & 0xff;
    }

    // define offset metadata
    for (int i = 0; i < 4; i++){
        image->data[i+10] = 138 >> (8*i) & 0xff;
    }

    // define width metadata
    for (int i = 0; i < 4; i++){
        image->data[i+18] = w >> (8*i) & 0xff;
    }

    // define height metadata
    for (int i = 0; i < 4; i++){
        image->data[i+22] = h >> (8*i) & 0xff;
    }

    // define bits per pixel metadata
    for (int i = 0; i < 2; i++){
        image->data[i+28] = 32 >> (8*i) & 0xff;
    }
