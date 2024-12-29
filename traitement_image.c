#include <stdio.h>
#include "mem.c"

struct pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct bmp_image {
    int size;
    int offset;
    int header_size;
    int width;
    int height;
    int bits_per_pixel;
    struct pixel *data;
};


/*
Objective : Load a BMP image
Input : file_name : the name of the file to load
Output : pointer to the image structure
*/

struct bmp_image * load_bmp(char * file_name){
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }


    // create the image structure
    struct bmp_image *image = malloc(sizeof(struct bmp_image));

    // Signature
    char b = fgetc(file);
    char m = fgetc(file);
    if (b != 'B' || m != 'M') {
        printf("Ce n'est pas un fichier BMP\n");
        return NULL;
    }

    // Size
    unsigned long int s[4];
    unsigned long int size = 0;
    for (int i = 0; i < 4; i++) {
        s[i] = fgetc(file);
        size += s[i] << (8 * i);
    }
    image->size = size;

    // Unused / Reserved
    for (int i = 0; i < 4; i++) {
        fgetc(file);
    }

    // Offset
    unsigned long int o[4];
    unsigned long int offset = 0;
    for (int i = 0; i < 4; i++) {
        o[i] = fgetc(file);
        offset += o[i] << (8 * i);
    }
    image->offset = offset;

    // Header size
    unsigned long int hs[4];
    unsigned long int header_size = 0;
    for (int i = 0; i < 4; i++) {
        hs[i] = fgetc(file);
        header_size += hs[i] << (8 * i);
    }
    image->header_size = header_size;

    // Width
    unsigned long int w[4];
    unsigned long int width = 0;
    for (int i = 0; i < 4; i++) {
        w[i] = fgetc(file);
        width += w[i] << (8 * i);
    }
    image->width = width;

    // Height
    unsigned long int h[4];
    unsigned long int height = 0;
    for (int i = 0; i < 4; i++) {
        h[i] = fgetc(file);
        height += h[i] << (8 * i);
    }
    image->height = height;

    // Unused / Planes
    for (int i = 0; i < 2; i++) {
        fgetc(file);
    }

    // Bits per pixel
    unsigned long int bpp[2];
    unsigned long int bits_per_pixel = 0;
    for (int i = 0; i < 2; i++) {
        bpp[i] = fgetc(file);
        bits_per_pixel += bpp[i] << (8 * i);
    }
    image->bits_per_pixel = bits_per_pixel;


    // Compression
    unsigned long int c[4];
    unsigned long int compression = 0;
    for (int i = 0; i < 4; i++) {
        c[i] = fgetc(file);
        compression += c[i] << (8 * i);
    }

    // Image size
    unsigned long int is[4];
    unsigned long int image_size = 0;
    for (int i = 0; i < 4; i++) {
        is[i] = fgetc(file);
        image_size += is[i] << (8 * i);
    }

    // X pixels per meter
    unsigned long int xppm[4];
    unsigned long int x_pixels_per_meter = 0;
    for (int i = 0; i < 4; i++) {
        xppm[i] = fgetc(file);
        x_pixels_per_meter += xppm[i] << (8 * i);
    }

    // Y pixels per meter
    unsigned long int yppm[4];
    unsigned long int y_pixels_per_meter = 0;
    for (int i = 0; i < 4; i++) {
        yppm[i] = fgetc(file);
        y_pixels_per_meter += yppm[i] << (8 * i);
    }

    // Unused / Number of colors
    unsigned long int nc[4];
    unsigned long int number_of_colors = 0;
    for (int i = 0; i < 4; i++) {
        nc[i] = fgetc(file);
        number_of_colors += nc[i] << (8 * i);
    }

    // Unused / Important colors
    unsigned long int ic[4];
    unsigned long int important_colors = 0;
    for (int i = 0; i < 4; i++) {
        ic[i] = fgetc(file);
        important_colors += ic[i] << (8 * i);
    }

    // Unused / channel bitmasks
    unsigned long int cb[16];
    for (int i = 0; i < 16; i++) {
        fgetc(file);
    }

    // Unused / color space type

    for (int i = 0; i < 4; i++) {
        fgetc(file);
    }

    // Unused / color space endpoints
    for (int i = 0; i < 36; i++) {
        fgetc(file);
    }

    // Unused / gamma for color space
    for (int i = 0; i < 4; i++) {
        fgetc(file);
    }

    // Unused / ICC profile
    for (int i = 0; i < 4; i++) {
        fgetc(file);
    }

    // Unused / ICC profile size
    for (int i = 0; i < 4; i++) {
        fgetc(file);
    }

    // Unused / reserved

    for (int i = 0; i < 16; i++) {
        fgetc(file);
    }

    // Unused / reserved

    for (int i = 0; i < 4; i++) {
        fgetc(file);
    }

    // Data
    image->data = malloc(sizeof(struct pixel) * width * height);
    for (int i = 0; i < width * height; i++) {
        image->data[i].b = fgetc(file);
        image->data[i].g = fgetc(file);
        image->data[i].r = fgetc(file);
        if (bits_per_pixel == 32) {
            image->data[i].a = fgetc(file);
        } else {
            image->data[i].a = 0;
        }
    }

    fclose(file);
    return image;
}

/*
Objective : Get a pixel from an image
Input : image : the image
        x : the x coordinate of the pixel
        y : the y coordinate of the pixel
Output : pointer to the pixel
*/
struct pixel * get_pixel(struct bmp_image *image, int x, int y){
    return &image->data[y * image->width + x];
}

/*
Objective : show a BMP image
Input : image : the image to show
*/
void show_bmp(struct bmp_image *image){
    for (int i = 0; i < image->width; i++) {
        for (int j = 0; j < image->height; j++) {
            struct pixel *p = get_pixel(image, i, j);
            int gray = (p->r + p->g + p->b + p->a) / 4;
            if (gray > 110){
                printf("##");
            } else {
                printf("  ");
            }
            //printf("%3d",get_pixel(image, i, j)->r);
        }
        printf("\n");
    }
}

/*
Objective : Save a BMP image
Input : image : the image to save
        file_name : the name of the file to save
*/
void save_bmp(struct bmp_image *image, char *file_name){
    FILE *file = fopen(file_name, "wb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    // Signature
    fputc('B', file);
    fputc('M', file);

    // Size
    for (int i = 0; i < 4; i++) {
        fputc((image->size >> (8 * i)) & 0xFF, file);
    }

    // Unused / Reserved
    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Offset
    for (int i = 0; i < 4; i++) {
        fputc((image->offset >> (8 * i)) & 0xFF, file);
    }

    // Header size
    for (int i = 0; i < 4; i++) {
        fputc((image->header_size >> (8 * i)) & 0xFF, file);
    }

    // Width
    for (int i = 0; i < 4; i++) {
        fputc((image->width >> (8 * i)) & 0xFF, file);
    }

    // Height
    for (int i = 0; i < 4; i++) {
        fputc((image->height >> (8 * i)) & 0xFF, file);
    }

    // Unused / Planes
    for (int i = 0; i < 2; i++) {
        fputc(1, file);
    }

    // Bits per pixel
    for (int i = 0; i < 2; i++) {
        fputc((image->bits_per_pixel >> (8 * i)) & 0xFF, file);
    }

    // Unused / Compression
    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Unused / Image size
    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Unused / X pixels per meter
    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }
    // Unused / Y pixels per meter
    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Unused / Number of colors
    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Unused / Important colors
    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Unused / channel bitmasks
    for (int i = 0; i < 16; i++) {
        fputc(0, file);
    }

    // Unused / color space type

    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Unused / color space endpoints
    for (int i = 0; i < 36; i++) {
        fputc(0, file);
    }

    // Unused / gamma for color space
    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Unused / ICC profile

    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Unused / ICC profile size
    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Unused / reserved

    for (int i = 0; i < 16; i++) {
        fputc(0, file);
    }

    // Unused / reserved

    for (int i = 0; i < 4; i++) {
        fputc(0, file);
    }

    // Data
    for (int i = 0; i < image->width * image->height; i++) {
        fputc(image->data[i].b, file);
        fputc(image->data[i].g, file);
        fputc(image->data[i].r, file);
        fputc(image->data[i].a, file);
    }

    fclose(file);
}
