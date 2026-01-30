#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include "image.h"
#include "sequence_point.h"

void trouver_pixel_depart(Image I, int *x_depart, int *y_depart);

void calculer_contour_ecran(Image I);

Liste_Point calculer_contour(Image I);

#endif /* _CONTOUR_H_ */