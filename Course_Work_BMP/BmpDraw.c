#include "BmpDraw.h"
void draw_square(Rgb** pixels, int x_l, int y_l, char color[], int side_long, int thickness, int flag, int H, int W, char c_fill[]){
    int b, g, r;
    sscanf(color, "%d.%d.%d", &b, &g, &r);
    //printf("%d %d %d", b, g, r);
    //цвета
    int t_down, t_up;
    if (thickness % 2 !=0){
        t_down =  thickness/2;
        t_up = thickness/2;
    }
    else{
        t_down =thickness/2;
        t_up = thickness/2 -1;
    }
    if (x_l > W && y_l>H) return;
    //толщина для квадрата
    int r_wall=0;
    int d_wall=0;
    int l_wall=0;
    int up_wall=0;
    if (x_l+side_long>W) r_wall = W;
    if (x_l <0){
        if (x_l+side_long < 0) return;
        l_wall = -1;
    }
    if (y_l<0){
        if (H-1-y_l-side_long>H) return;
        up_wall = H;
    }
    if (y_l>=H){
        return;
    }
    if (x_l>=W) return;
    y_l = H-1-y_l;
    if (y_l-side_long<0) d_wall = -1;
    //if (((l_wall == -1) & (r_wall == W)) || ((up_wall == H) & (d_wall == -1))) return; // без диагоналей пока что
    // границы
    if (flag==1){
        int b_f, g_f, r_f;
        sscanf(c_fill, "%d.%d.%d", &b_f, &g_f, &r_f);
        int x1 =x_l+1;
        int y1 =y_l-1;
        int x2 = x1+side_long-1;
        int y2= y_l-side_long+1;
        if (up_wall == H) y1 = H-1;
        if (l_wall==-1) x1= 0;
        if (d_wall ==-1) y2=0;
        if (r_wall==W) x2= W-1;
        for (int y=y2; y<=y1; y++){
            for (int x=x1; x<=x2; x++){
                pixels[y][x].b=b_f;
                pixels[y][x].g=g_f;
                pixels[y][x].r=r_f;
            }
        }
    }
    //заливка
    for (int c=-t_down; c<t_up+1; c++){
        for (int x=x_l+c; x<=x_l+side_long-c; x++){
            if (x<0) continue;
            if (x==W) break;
            if (up_wall!=H){
                if (y_l+c>=0 && y_l+c<=H-1){
                    pixels[y_l-c][x].b=b; //+c вроде вниз
                    pixels[y_l-c][x].g=g;
                    pixels[y_l-c][x].r=r;
                }
            }
            if (d_wall != -1){
                if (y_l-side_long+c>=0 && y_l-side_long+c<=H-1){
                    pixels[y_l-side_long+c][x].b=b;
                    pixels[y_l-side_long+c][x].g=g;
                    pixels[y_l-side_long+c][x].r=r;
                }
            }
        }
    }
    // верх и низ
    for (int c=-t_down; c<t_up+1; c++){
        for (int y=y_l-side_long-t_down; y<=y_l+t_up; y++){
            if (y<0) continue;
            if (y==H) break;
            if (l_wall !=-1){
                if (x_l+c >=0 && x_l+c<W){
                    pixels[y][x_l+c].b=b;
                    pixels[y][x_l+c].g=g;
                    pixels[y][x_l+c].r=r;
                }
            }
            if (r_wall!=W){
                if (x_l+side_long+c >=0 && x_l+side_long+c<W) {
                    pixels[y][x_l + side_long - c].b = b;
                    pixels[y][x_l + side_long - c].g = g;
                    pixels[y][x_l + side_long - c].r = r; //+с внутрь будет при четных
                }
            }
        }
    }
    // бока
    int x_c1, x_c2, y_c1, y_c2;
    x_c1 = x_l+1;
    x_c2 = x_l+side_long-1;
    y_c1 = y_l-side_long;
    y_c2 = y_l-1;
    //printf("[%d]x_c1:%d y_c1:%d %d %d", x_l, x_c1, y_c1, x_c2, y_c2);
    //координаты для диагонали 1
    int dx = x_c2-x_c1;
    int dy = y_c2-y_c1;
    int di_1 = 2*dy-dx;
    int d1 = 2*dy;
    int d2 = 2*(dy-dx);
    for (int c=-t_down; c<t_up+1; c++){
        int yy=y_c1;
        for (int x=x_c1; x<=x_c2; x++){
            if (di_1<=0) di_1+=d1;
            else{
                yy++;
                di_1+=d2;
            }
            if (x==W || yy+c==H) break;
            if (x>0 && yy+c<=H && yy+c>=0){
                pixels[yy+c][x].b = b;
                pixels[yy+c][x].g = g;
                pixels[yy+c][x].r = r;
            }
        }
    }
    //1ая диагональ
    int x_c3, x_c4, y_c3, y_c4; // 3ая вверху слева
    x_c3 = x_l+1;
    x_c4 = x_l+side_long-1;
    y_c3 = y_l;
    y_c4 = y_l-side_long;
    int dx_2 = x_c4-x_c3;
    int dy_2 = y_c3 - y_c4;
    int di_2 = 2*dy_2 - dx_2;
    int d1_2 =2*dy_2;
    int d2_2 =2*(dy_2-dx_2);
    for (int c=-t_down; c<t_up+1; c++){
        int yyy=y_c3;
        for (int x=x_c3; x<=x_c4; x++){
            if (di_2<=0) di_2+=d1_2;
            else{
                yyy--;
                di_2+=d2_2;
            }
            if (x==W || yyy<0) break;
            if (x>=0 && yyy+c>=0 && yyy+c<=H){
                pixels[yyy+c][x].b = b;
                pixels[yyy+c][x].g = g;
                pixels[yyy+c][x].r = r;
            }
        }
    }
    // 2ая диагональ
}

void draw_circle(Rgb** pixels, char coord[], int radius, char color[], int thickness, int flag, int H, int W, char c_fill[]){
    int b, g, r;
    sscanf(color, "%d.%d.%d", &b, &g, &r);
    //цвета
    int x, y;
    sscanf(coord, "%d.%d", &x, &y);
    y=H-1-y;
    //координаты
    /*
    pixels[y][x].b=0;
    pixels[y][x].g=0;
    pixels[y][x].r=0;*/
    //центр закрашивать
    int t_down, t_up;
    if (thickness % 2 !=0){
        t_down =  thickness/2;
        t_up = thickness/2;
    }
    else{
        t_down =thickness/2;
        t_up = thickness/2 -1;
    }
    //printf("%d %d", t_down, t_up);
    //толщина

    if (flag==1){
        int b_f, g_f, r_f;
        sscanf(c_fill, "%d.%d.%d", &b_f, &g_f, &r_f);
        int x_l, y_l, x_r, y_r;
        x_l = x-radius;
        x_r = x+radius;
        y_l = y+radius;
        y_r = y-radius;
        for (int i=y_r; i<y_l; i++){
            if (i < 0 || i>=H) continue;
            for (int j=x_l; j<x_r; j++){
                if (j>=W || j<0) continue;
                if ((x-j)*(x-j) + (y-i)*(y-i) < radius*radius){
                    pixels[i][j].b=b_f;
                    pixels[i][j].g=g_f;
                    pixels[i][j].r=r_f;
                }
            }
        }
    } // заливка
    int xi = 0;
    int yi=radius;
    int dd = 2*(xi-yi+1);
    for (int k=-t_down; k<t_up+1; k++){
        if (y+yi-k < H && y+yi-k>=0 && x+xi<W && x+xi>=0){
            pixels[y+yi-k][x+xi].b=b;
            pixels[y+yi-k][x+xi].g=g;
            pixels[y+yi-k][x+xi].r=r;
        }
        if (y-yi+k>=0 && y-yi+k<H && x+xi>=0 && x+xi <W){
            pixels[y-yi+k][x+xi].b=b;
            pixels[y-yi+k][x+xi].g=g;
            pixels[y-yi+k][x+xi].r=r;
        }
    }
    // центральные пиксели под и над радиусом
    while (yi>0){
        int fl=0;
        int di, si;
        if (dd==0){
            xi++;
            yi--;
            dd+=2*(xi-yi+1);
            fl=1;
        }
        else if(dd<0){
            di = 2*(dd+yi)-1;
            if (di<=0){
                xi++;
                dd+=2*xi+1;
                fl=2;
            }
            else{
                xi++;
                yi--;
                dd+=2*(xi-yi+1);
                fl=1;
            }
        }
        else{
            si = 2*(dd-xi)-1;
            if (si<=0){
                xi++;
                yi--;
                dd+=2*(xi-yi+1);
                fl=1;
            }
            else{
                yi--;
                dd+=1-2*yi;
                fl=3;
            }
        }
        if (y+yi <H && y+yi>=0){
            //правая сторона
            if (x+xi<W && x+xi>=0){
                pixels[y+yi][x+xi].b=b;
                pixels[y+yi][x+xi].g=g;
                pixels[y+yi][x+xi].r=r; //основная окружность толщины 1
                if (fl==3){
                    for (int c=-t_down; c<t_up+1; c++){
                        if (x+xi-c<W && x+xi-c>=0){
                            pixels[y+yi][x+xi-c].b=b;
                            pixels[y+yi][x+xi-c].g=g;
                            pixels[y+yi][x+xi-c].r=r;
                        }
                    }
                }
                else if (fl==2){
                    for (int c=-t_down; c<t_up+1; c++){
                        if (y+yi-c<H && y+yi-c>=0){
                            pixels[y+yi-c][x+xi].b=b;
                            pixels[y+yi-c][x+xi].g=g;
                            pixels[y+yi-c][x+xi].r=r;
                        }
                    }
                }
                else{
                    for (int c=-t_down; c<t_up+1; c++){
                        if (y+yi-c<H && y+yi-c>=0 && x+xi-c<W && x+xi-c>=0){
                            pixels[y+yi-c][x+xi].b=b;
                            pixels[y+yi-c][x+xi].g=g;
                            pixels[y+yi-c][x+xi].r=r;
                            pixels[y+yi][x+xi-c].b=b;
                            pixels[y+yi][x+xi-c].g=g;
                            pixels[y+yi][x+xi-c].r=r;
                        }
                    }
                }
            }
            if (x-xi>=0 && x-xi<W){ //левая сторона
                pixels[y+yi][x-xi].b=b;
                pixels[y+yi][x-xi].g=g;
                pixels[y+yi][x-xi].r=r;
                if (fl==3){
                    for (int c=-t_down; c<t_up+1; c++){
                        if (x-xi+c<W && x-xi+c>=0){
                            pixels[y+yi][x-xi+c].b=b;
                            pixels[y+yi][x-xi+c].g=g;
                            pixels[y+yi][x-xi+c].r=r;
                        }
                    }
                }
                else if (fl==2){
                    for (int c=-t_down; c<t_up+1; c++){
                        if (y+yi-c<H && y+yi-c>=0){
                            pixels[y+yi-c][x-xi].b=b;
                            pixels[y+yi-c][x-xi].g=g;
                            pixels[y+yi-c][x-xi].r=r;
                        }
                    }
                }
                else{
                    for (int c=-t_down; c<t_up+1; c++){
                        if (y+yi-c<H && y+yi-c>=0 && x-xi-c<W && x-xi-c>=0){
                            pixels[y+yi-c][x-xi].b=b;
                            pixels[y+yi-c][x-xi].g=g;
                            pixels[y+yi-c][x-xi].r=r;
                            pixels[y+yi][x-xi+c].b=b;
                            pixels[y+yi][x-xi+c].g=g;
                            pixels[y+yi][x-xi+c].r=r;
                        }
                    }
                }
            }
        }
        //верхняя часть
        if (y-yi >=0 && y-yi<H){
            if (x+xi<W && x+xi>=0){
                pixels[y-yi][x+xi].b=b;
                pixels[y-yi][x+xi].g=g;
                pixels[y-yi][x+xi].r=r;
                if (fl==3){
                    for (int c=-t_down; c<t_up+1; c++){
                        if (x+xi-c<W && x+xi-c>=0){
                            pixels[y-yi][x+xi-c].b=b;
                            pixels[y-yi][x+xi-c].g=g;
                            pixels[y-yi][x+xi-c].r=r;
                        }
                    }
                }
                else if (fl==2){
                    for (int c=-t_down; c<t_up+1; c++){
                        if (y-yi+c<H && y-yi+c>=0){
                            pixels[y-yi+c][x+xi].b=b;
                            pixels[y-yi+c][x+xi].g=g;
                            pixels[y-yi+c][x+xi].r=r;
                        }
                    }
                }
                else{
                    for (int c=-t_down; c<t_up+1; c++){
                        if (y-yi+c<H && y-yi+c>=0 && x+xi-c<W && x+xi-c>=0){
                            pixels[y-yi+c][x+xi].b=b;
                            pixels[y-yi+c][x+xi].g=g;
                            pixels[y-yi+c][x+xi].r=r;
                            pixels[y-yi][x+xi-c].b=b;
                            pixels[y-yi][x+xi-c].g=g;
                            pixels[y-yi][x+xi-c].r=r;
                        }
                    }
                }

            }
            if (x-xi>=0 && x-xi<W){
                pixels[y-yi][x-xi].b=b;
                pixels[y-yi][x-xi].g=g;
                pixels[y-yi][x-xi].r=r;

                if (fl==3){
                    for (int c=-t_down; c<t_up+1; c++){
                        if (x-xi+c<W && x-xi+c>=0){
                            pixels[y-yi][x-xi+c].b=b;
                            pixels[y-yi][x-xi+c].g=g;
                            pixels[y-yi][x-xi+c].r=r;
                        }
                    }
                }
                else if (fl==2){
                    for (int c=-t_down; c<t_up+1; c++){
                        if (y-yi+c<H && y-yi+c>=0){
                            pixels[y-yi+c][x-xi].b=b;
                            pixels[y-yi+c][x-xi].g=g;
                            pixels[y-yi+c][x-xi].r=r;
                        }
                    }
                }
                else{
                    for (int c=-t_down; c<t_up+1; c++){
                        if (y-yi+c<H && y-yi+c>=0 && x-xi+c<W && x-xi+c>=0){
                            pixels[y-yi+c][x-xi].b=b;
                            pixels[y-yi+c][x-xi].g=g;
                            pixels[y-yi+c][x-xi].r=r;
                            pixels[y-yi][x-xi+c].b=b;
                            pixels[y-yi][x-xi+c].g=g;
                            pixels[y-yi][x-xi+c].r=r;
                        }
                    }
                }
            }
        }
        //нижняя часть
    }
    // круг
}
