#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "contour.h"

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage : %s <fichier_image.pbm>\n", argv[0]);
        return 1;
    }

    Image I = lire_fichier_image(argv[1]); 

    Liste_Point contour = calculer_contour(I);

    int w = largeur_image(I);
    int h = hauteur_image(I);
    int nb_segments = contour.taille - 1;
    
    printf("Fichier: %s\n", argv[1]);
    printf("Dimensions: %d x %d\n", w, h);
    printf("Nombre de segments: %d\n", nb_segments);
    printf("\n");
    
    contour = supprimer_liste_Point(contour);
    supprimer_image(&I);
    
    return 0;
}