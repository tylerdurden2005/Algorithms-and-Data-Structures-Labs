#ifndef BMPCHANGE_H
#define BMPCHANGE_H
#include "BmpRead.h"
void changer_color(Rgb** pixels, int col, int new_fill, int W, int H);
void rotate(Rgb** pixels, int degree, int* H, int* W, int x_l, int y_l, int x_r, int y_r);
#endif //BMP_CW2_BMPCHANGE_H
