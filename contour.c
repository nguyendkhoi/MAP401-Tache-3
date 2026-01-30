#include <stdio.h>
#include <stdlib.h>
#include "contour.h"
#include "image.h"

void trouver_pixel_depart(Image I, int *x_depart, int *y_depart) {
    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);
    
    for (int y = 1; y <= H; y++) {
        for (int x = 1; x <= L; x++) {
            if (get_pixel_image(I, x, y) == NOIR) {
                *x_depart = x - 1;
                *y_depart = y - 1;
                return;
            }
        }
    }
    *x_depart = -1;
    *y_depart = -1;
}

void avancer(int *x, int *y, int direction) {
    switch(direction) {
        case 0: (*x)++; break; // Est
        case 1: (*y)--; break; // Nord
        case 2: (*x)--; break; // Ouest
        case 3: (*y)++; break; // Sud
    }
}

int est_bordure(Image I, int x, int y, int direction) {
    int x_gauche, y_gauche;
    int x_droite, y_droite;
    
    switch(direction) {
        case 0:
            x_gauche = x + 1; y_gauche = y;
            x_droite = x + 1; y_droite = y + 1;
            break;
        case 1:
            x_gauche = x;     y_gauche = y;
            x_droite = x + 1; y_droite = y;
            break;
        case 2: 
            x_gauche = x;     y_gauche = y + 1;
            x_droite = x;     y_droite = y;
            break;
        case 3:
            x_gauche = x + 1; y_gauche = y + 1;
            x_droite = x;     y_droite = y + 1;
            break;
    }
    
    Pixel pG = get_pixel_image(I, x_gauche, y_gauche);
    Pixel pD = get_pixel_image(I, x_droite, y_droite);
    
    return (pD == NOIR && pG == BLANC);
}

void memoriser_position(int x, int y) {
    printf(" %.1f %.1f\n", (double)x, (double)y);
}

void calculer_contour(Image I) {
    int x_start, y_start;
    trouver_pixel_depart(I, &x_start, &y_start);
    
    if (x_start == -1) {
        printf("L'image est vide (toute blanche).\n");
        return;
    }

    int x = x_start;
    int y = y_start;
    int direction = 0; 
    
    memoriser_position(x, y);
    
    int boucle = 1;
    while (boucle) {
        
        int d_gauche = (direction + 1) % 4;
        int d_droite = (direction + 3) % 4;
        
        if (est_bordure(I, x, y, d_gauche)) {
            direction = d_gauche;
        } else if (est_bordure(I, x, y, direction)) {
        } else if (est_bordure(I, x, y, d_droite)) {
            direction = d_droite;
        } else {
            direction = (direction + 2) % 4;
        }
        
        avancer(&x, &y, direction);
        
        memoriser_position(x, y);
        
        if (x == x_start && y == y_start) {
            boucle = 0;
        }
    }
}