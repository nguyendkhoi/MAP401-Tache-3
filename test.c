#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "contour.h"
#include "sequence_point.h"

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
    
    string fichier_nom = argv[1];
    size_t pos = fichier_nom.find('.pbm');
    string word = fichier_nom.substr(0, pos).append(".eps");
    
    File *f = fopen(word, "w");

    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n", "%%%%BoundingBox 0 0 %d %d\n", w, h);
    fprintf(f, "/l {lineto} def\n", "/m {moveto} def\n", "/s {stroke} def\n");

    Cellule_Liste_Point *LP = contour.first;
    Point P = LP->data;

    fprintf(f, "%d %d m\n", P.x, P.y);

    Cellule_Liste_Point *suivLP= LP->suiv;

    while (suivLP != NULL) {
        Point suivPoint = suivLP->data;
        fprintf(f, "%d %d l\n", suivPoint.x, suivPoint.y);
		suivLP = suivLP->suiv;
    }

    fprintf(f, "%d %d l\n", P.x, P.y);

    string type;
    if (argv[2] == 1) type = "stroke";
    else type = "fill";

    fprintf(f, "0 setlinewith %s\n", type);
    fprintf(f, "showpage");

    contour = supprimer_liste_Point(contour);
    supprimer_image(&I);
    
    return 0;
}