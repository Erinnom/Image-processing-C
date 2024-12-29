#include "dump.c"
#include "traitement_image.c"

int main() {
    //dump_file("signature_white_bg.bmp", 'c', 200);
    struct bmp_image *image = load_bmp("color.bmp");
    //show_bmp(image);

    save_bmp(image, "color2.bmp");
    return 0;
}
