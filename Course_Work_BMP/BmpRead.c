#include "BmpRead.h"

Rgb** read_bmp(char file_name[], BmpFileHeader* bmfh, BmpInfoHeader* bmif){
    FILE *f = fopen(file_name, "r");
    if (!f){
        printf("Невозможно открыть файл!\n");
        exit(40);
    }
    fread(bmfh, 1, sizeof(BmpFileHeader), f);
    if (strncmp(bmfh->signature, "BM", 2)!=0){
        printf("Файл не формата Bmp!\n");
        exit(40);
    }
    fread(bmif, 1, sizeof(BmpInfoHeader), f);

    if (bmif->compression !=0){
        printf("Файл сжат!\n");
        exit(40);
    }
    if (bmif->bitsPerPixel !=24){
        printf("Недопустимая глубина цвета!\n");
        exit(40);
    }
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    Rgb** arr = malloc(H * sizeof(Rgb*)); //строки пикселей по факту
    for(int i = 0; i < H; i++){
        arr[i] = malloc(W * sizeof(Rgb) + (W * 3) % 4); //под 1 строку выделяем
        fread(arr[i], 1, W * sizeof(Rgb) + (W * 3) % 4,f);
    }
    fclose(f);
    return arr;
}

void free_bmp(BmpFileHeader* bmfh, BmpInfoHeader* bmif, Rgb** pixels){
    unsigned int H = bmif->height;
    free(bmfh);
    free(bmif);
    for (int i =0; i<H; i++){
        free(pixels[i]);
    }
    free(pixels);
}

void info_printer(BmpFileHeader* bmfh, BmpInfoHeader* bmif){
    printf("Signature: %c%c\n", bmfh->signature[0], bmfh->signature[1]);
    printf("FileSize: %d\n", bmfh->filesize);
    printf("PixelArrOffset: %d\n", bmfh->pixelArrOffset);
    printf("HeaderSize: %d\n", bmif->headerSize);
    printf("Width: %d\n", bmif->width);
    printf("Height: %d\n", bmif->height);
    printf("Planes: %d\n", bmif->planes);
    printf("BitsPerPixel: %d\n", bmif->bitsPerPixel);
    printf("Compression: %d\n", bmif->compression);
    printf("ImageSize: %d\n", bmif->imageSize);
    printf("xPixelsPerMeter: %d\n", bmif->xPixelsPerMeter);
    printf("yPixelsPerMeter: %d\n", bmif->yPixelsPerMeter);
    printf("ColorsInColorTable: %d\n", bmif->colorsInColorTable);
    printf("ImportantColorCount: %d\n", bmif->importantColorCount);
}
