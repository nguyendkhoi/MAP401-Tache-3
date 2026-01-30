#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include "image.h"

BOOL trouver_pixel_depart(Image I, int *x_depart, int *y_depart);

void calculer_contour_ecran(Image I);

#endif /* _CONTOUR_H_ */