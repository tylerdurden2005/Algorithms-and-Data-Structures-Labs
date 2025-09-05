#include "BmpChange.h"
void changer_color(Rgb** pixels, int col, int new_fill, int W, int H){
    for (int i=0; i<H;i++){
        for (int j=0; j<W;j++){
            if (col==0) pixels[i][j].b = new_fill;
            else if(col==1) pixels[i][j].g = new_fill;
            else pixels[i][j].r = new_fill;
        }
    }
}

void rotate(Rgb** pixels, int degree, int* Hi, int* Wi, int x_l, int y_l, int x_r, int y_r){
    int H=*Hi;
    int W=*Wi;
    if (x_l==x_r && y_l==y_r){
        return;
    }
    //
    if (x_l>x_r){
        int x_pr = x_l;
        x_l=x_r;
        x_r=x_pr;
    }
    if (y_l>y_r){
        int y_pr = y_l;
        y_l=y_r;
        y_r=y_pr;
    }
    // неправильные входные координаты
    if (x_l<0 && y_l <0){
        x_l =0;
        y_l=0;
    }
    else if(y_l<0) y_l=0;
    else if(x_l<0) x_l=0;

    if(x_r>=*Wi && y_r>=*Hi){
        x_r = (*Wi)-1;
        y_r= (*Hi)-1;
    }
    else if(y_r>=*Hi) y_r=(*Hi)-1;
    else if(x_r>=*Wi) x_r=(*Wi)-1;
    //максимальные координаты
    int flag = 0;
    if ((degree==90 || degree==270) && (y_l==0 && x_l==0 && x_r == (*Wi)-1 & y_r == (*Hi)-1)) flag=1;
    //flag
    y_l=H-1-y_l;
    y_r=H-1-y_r;
    H=y_l-y_r+1;
    W=x_r-x_l+1;
    //printf("x_r:%d %d\n",x_r, x_l);
    //printf("y_r:%d %d\n",y_r, y_l);
    //координаты смена
    Rgb** arr = malloc(H * sizeof(Rgb*));
    int p_i = y_r;
    for(int i = 0; i < H; i++) {
        arr[i] = malloc(W * sizeof(Rgb)+(W * 3) % 4);
        int p_j= x_l;
        for (int j = 0; j < W; j++) {
            arr[i][j] = pixels[p_i][p_j++];
        }
        p_i++;
    }//копия для пикселей
    if (degree==180){
        int c=H-1;
        int k;
        for (int y = y_r; y < y_l+1; y++) {
            k=W-1;
            for (int x = x_l; x < x_r+1; x++) {
                pixels[y][x] = arr[c][k--];// Переносим значения пикселей
            }
            c--;
        }
    }//180 градусов
    else if(degree==90 || degree==270){
        if (flag==1){
            for (int i=0; i<H;i++){
                free(pixels[i]);
            }
            pixels = (Rgb**)realloc(pixels, W * sizeof(Rgb*));
            for (int i=0; i<W;i++){
                pixels[i] = malloc(H * sizeof(Rgb) + (H * 3) % 4); //меняем размер массива пикселей
            }
            (*Wi)=H; //меняем исходные W & H
            (*Hi)=W;
        }
        int c=H-1;
        /*
        printf("h:[%d]", (*Hi));
        printf("w:[%d]", (*Wi));
        printf("x_fin[%d]", (*Wi) -y_l-2);
        printf("x_start[%d]", (*Wi) -y_r-1);
        printf("y_fin[%d]", (*Hi) -x_l-1);
        printf("y_start[%d]", (*Hi) -x_r-1);*/
        if (degree==90){ //заполняем справа влево сверху вниз
            for (int x=(*Wi)-y_r-1; x>(*Wi)-y_l-2; x--){
                int k=0;
                for (int y=(*Hi)-x_l-1; y>(*Hi)-x_r-1;y--){
                    pixels[y][x]=arr[c][k];
                    k++;
                }
                c--;
            }
        }
        else{//заполняем слева направо снизу вверх
            for (int x=(*Wi)-y_l-1; x<(*Wi)-y_r; x++){
                int k=0;
                for (int y=(*Hi)-x_r-1; y<(*Hi)-x_l;y++){
                    pixels[y][x]=arr[c][k++];
                }
                c--;
            }
        }
    }//90 and 270

    for (int i=0; i<H; i++){
        free(arr[i]);
    }
    free(arr);
}

