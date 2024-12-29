#include <stdio.h>
/*
Objective: Dump the content of a file in hexadecimal/Decimal/ASCII
Input:
    - file_name: the name of the file to dump
    - mode: the mode of the dump (x: hexadecimal, d: decimal, c: ASCII, b: binary)
*/
void dump_file(char *file_name, char mode,int max_dump){
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    printf("Dump of : %s\n",file_name);
    unsigned int c = fgetc(file);
    int count = 0;
    while (c != EOF && count < max_dump) {
        if (mode == *"x") {
            printf("%02x ", c);
        } else if (mode == *"d") {
            printf("%3d ", c);
        } else if (mode == *"c") {
            if (c < 123 && c > 64) {
                printf("%3c ", c);
            } else {
                printf("%3d ", c);
            }
        } else if (mode == *"b") {
            printf("%08b ", c);
        }
        int a = 20;
        if (count%a == a-1) {
            printf("\n");
        }
        c = fgetc(file);
        count++;
    }
    //fclose(file);
    printf("\nEnd of dump\n");
}
