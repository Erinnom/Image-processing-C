#include "dump.c"
#include "traitement_image.c"

int main() {
    // Load an image
    struct image *image = load_image("color.bmp");

    // turn the image to gary

    for (int i = 0; i < image->width; i++){
        for (int j = 0; j < image->height; j++){
            struct pixel *p = get_pixel(image,i,j);
            int moy = (p->r + p->g + p->b)/3;

            p->r = moy;
            p->g = moy;
            p->b = moy;

            set_pixel(image,i,j,p);
        }
    }

    // Save the image
    save_image(image, "test2.bmp");
    clear_memory();
    return 0;
}
