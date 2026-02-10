#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "contour.h"
#include "sequence_point.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage : %s <fichier_image.pbm> <1 (stroke) | 2 (fill)>\n", argv[0]);
        return 1;
    }
    
    char output_filename[256];
    strcpy(output_filename, argv[1]);
    char *dot = strrchr(output_filename, '.');
    strcat(output_filename, ".eps");

    FILE *f = fopen(output_filename, "w");
    if (f == NULL) {
        printf("Erreur : Impossible de creer le fichier %s\n", output_filename);
        return 1;
    }

    Image I = lire_fichier_image(argv[1]); 
    Liste_Point contour = calculer_contour(I);

    int w = largeur_image(I);
    int h = hauteur_image(I);

    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", w, h);

    fprintf(f, "/l {lineto} def\n");
    fprintf(f, "/m {moveto} def\n");
    fprintf(f, "/s {stroke} def\n");

    Cellule_Liste_Point *LP = contour.first;

    Point P = LP->data;
    fprintf(f, "%f %f m\n", P.x, P.y);

    Cellule_Liste_Point *suivLP= LP->suiv;
    while (suivLP != NULL) {
        Point suivPoint = suivLP->data;
        fprintf(f, "%f %f l\n", suivPoint.x, suivPoint.y);
		suivLP = suivLP->suiv;
    }

    fprintf(f, "%f %f l\n", P.x, P.y);

    if (strcmp(argv[2], "1") == 0) {
        fprintf(f, "s\n");
    }
    else {
        fprintf(f, "fill\n");
    }

    fprintf(f, "showpage");

    fclose(f);

    contour = supprimer_liste_Point(contour);
    supprimer_image(&I);
    
    return 0;
}