#ifndef BMPREAD_H
#define BMPREAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack (1)
typedef struct {
    unsigned char signature[2];
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BmpFileHeader;

typedef struct {
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BmpInfoHeader;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;
#pragma pop
Rgb** read_bmp(char name[], BmpFileHeader* b1, BmpInfoHeader* b2);
void free_bmp(BmpFileHeader* b1, BmpInfoHeader* b2, Rgb** arr);
void info_printer(BmpFileHeader* b1, BmpInfoHeader* b2);
#endif //BMPREAD_H
