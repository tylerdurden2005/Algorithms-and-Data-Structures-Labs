#ifndef BMPDRAW_H
#define BMPDRAW_H
#include "BmpRead.h"
void draw_square(Rgb** pixels, int x_l, int y_l, char color[], int side_size, int thickness, int flag, int H, int W, char c_fill[]);
void draw_circle(Rgb** pixels, char coord[], int radius, char color[], int thickness, int flag, int H, int W, char c_fill[]);
#endif //BMP_CW2_BMPDRAW_H
