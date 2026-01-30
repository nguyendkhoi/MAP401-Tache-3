#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "contour.h"

int main(int argc, char **argv) {
    Image I;

    if (argc < 2) {
        printf("Usage : %s <fichier_image.pbm>\n", argv[0]);
        return 1;
    }

    I = lire_fichier_image(argv[1]);
    
    calculer_contour_ecran(I);
    
    return 0;
}