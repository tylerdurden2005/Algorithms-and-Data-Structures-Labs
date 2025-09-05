#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include "BmpChange.h"
#include "BmpDraw.h"
#include "consol.h"
int main(int argc, char* argv[]) {
    char name[50] = "./";
    char file_outname[50] = "./out.bmp";
    const char* short_options = "Ho:I:i:";
    const struct option long_options[] = {
            { "help", no_argument, NULL, 'H' }, //
            { "output", required_argument, NULL, 'p' },
            { "info", required_argument, NULL, 'I' },//
            { "input", required_argument, NULL, 'i' },

            { "squared_lines", no_argument, NULL, 'S' }, //
            { "left_up", required_argument, NULL, 'u' },
            { "side_size", required_argument, NULL, 'l' }, //
            { "thickness", required_argument, NULL, 't' }, //
            { "color", required_argument, NULL, 'o' },
            { "fill", no_argument, NULL, 'b' }, //
            { "fill_color", required_argument, NULL, 'f' },

            { "rgbfilter", no_argument, NULL, 'F' }, //
            { "component_name", required_argument, NULL, 'n' }, //
            { "component_value", required_argument, NULL, 'v' }, //

            { "rotate", no_argument, NULL, 'R' }, //
            { "right_down", required_argument, NULL, 'd' },
            { "angle", required_argument, NULL, 'a' }, //

            { "circle", no_argument, NULL, 'C' }, //
            { "center", required_argument, NULL, 'c' },
            { "radius", required_argument, NULL, 'r' }, //
            { NULL, 0, NULL, 0 }
    };
    //printf("argc: %d\n", argc);
    char** arg_f1 = malloc(sizeof(char*)*6); //1.0 - left(), 1.1-side, 1.2 - thickness() 1.3 - color(), 1.4-flag(), 1.5 - color for fill()
    for (int i=0; i<6; i++){
        arg_f1[i] = malloc(sizeof(char)*10);
        arg_f1[i][0] = '\0';
    }
    char** arg_f2 = malloc(sizeof(char*)*2);
    for (int i=0; i<2; i++){
        arg_f2[i] = malloc(sizeof(char)*10);
        arg_f2[i][0] = '\0';     // заполняется полностью 2.0 - компонент, 2.1 - значение от 0-255
    }
    char** arg_f3 = malloc(sizeof(char*)*3); // 3.0 - left(внешняя переменная), 3.1 - right, 3.2 - угол
    for (int i=0; i<3; i++){
        arg_f3[i] = malloc(sizeof(char)*10);
        arg_f3[i][0] = '\0';
    }
    char** arg_f4 = malloc(sizeof(char*)*6); //4.0 - center, 4.1-radius, 4.2 - thickness() 4.3 - color, 4.4-flag, 4.5 - color for fill
    for (int i=0; i<6; i++){
        arg_f4[i] = malloc(sizeof(char)*10);
        arg_f4[i][0] = '\0';
    }
    // общие переменные
    int flag=0;
    int fill_flag;
    char thickness[15];
    thickness[0] = '\0';
    char left_up[20];
    left_up[0]='\0';
    char color[15];
    color[0] ='\0';
    char fill_color[15];
    fill_color[0] = '\0';
    //выделение под аргументы память
    int opt;
    opterr = 0;
    while ((opt = (getopt_long(argc, argv, short_options, long_options, NULL)))!=-1){
        switch(opt){
            case 'H':
                if (argc>2){
                    printf("Флаг help не ожидает дополнительных аргументов!\n");
                    exit(40);
                }
                flag = 7;
                break;
            case 'S': //функции
            case 'F':
            case 'R':
            case 'C':
            case 'I':
                if (opt=='I'){
                    if (argc<2){
                        printf("Недостаточно параметров!\n");
                        exit(40);
                    }
                    if (argc>3){
                        printf("Флаг info не ожидает дополнительных параметров!\n");
                        exit(40);
                    }
                }
                else if(opt=='F' && argc <=6){
                    printf("Недостаточно параметров!\n");
                    exit(40);
                }
                else if(opt=='R' && argc <=8){
                    printf("Недостаточно параметров!\n");
                    exit(40);
                }
                else if((opt == 'C' || opt=='S') && argc<=10){
                    printf("Недостаточно параметров!\n");
                    exit(40);
                }
                if (opt=='S')flag =1;
                else if(opt=='F') flag=2;
                else if (opt=='R') flag=3;
                else if (opt=='C') flag=4;
                else flag=6;
                break;
            case 'b': //флаг заливки
                fill_flag=1;//1.4, 4.4
                break;
            case 'i':
            case 'p':
                if (optarg[0] == '-'){
                    printf("%s\n", "Аргумент пропущен!");
                    exit(40);
                }
                if (opt=='p') strcpy(file_outname, optarg);
                if (opt=='i') strcat(name, optarg);
                break;
            case 'd':
            case 'u': //координаты
            case 'c':
                if (optarg[0] == '-' && optarg[1]=='-'){
                    printf("%s\n", "Аргумент пропущен!");
                    exit(40);
                }
                // error need
                char* ptr = malloc((strlen(optarg)+1)*sizeof(char));
                strcpy(ptr, optarg);
                char* token = strtok(ptr, ".");
                while (token!= NULL) {
                    int j;
                    if (token[0] == '-') j=1;
                    else j=0;
                    for (j;j<strlen(token);j++){
                        if (!isdigit(token[j])){
                            printf( "Аргумент не число!\n");
                            exit(40);
                        }
                    }
                    token = strtok(NULL, ".");
                }
                free(ptr);
                if (opt=='d'){
                    strcpy(arg_f3[1], optarg); //3.1
                }
                else if(opt=='c'){
                    strcpy(arg_f4[0], optarg); //4.0
                }
                else strcpy(left_up, optarg); //1.0, 3.0
                break;
            case 'o': //цвета
            case 'f':
                if (optarg[0] == '-' && optarg[1]=='-'){
                    printf("Аргумент пропущен!\n");
                    exit(40);
                }
                //error
                char* p = malloc((strlen(optarg)+1)*sizeof(char));
                strcpy(p, optarg);
                char* t = strtok(p, ".");
                while (t!= NULL) {
                    if (strlen(t)>3){
                        printf( "Аргумент для компонента цвета не может быть больше 3х значного числа!\n");
                        exit(40);
                    }
                    for (int i = 0; i < strlen(t); i++) {
                        if (!isdigit(t[i])) {
                            printf( "Аргумент не число!\n");
                            exit(40);
                        }
                    }
                    t = strtok(NULL, ".");
                }
                free(p);
                if (opt == 'o') strcpy(color, optarg);
                else strcpy(fill_color, optarg); //1.5, 4.5
                break;
            case 'n':
                //printf("%s\n", optarg);
                if (optarg[0] == '-' ){
                    printf( "Аргумент пропущен!\n");
                    exit(40);
                }
                if (strcmp(optarg, "blue")!=0 && strcmp(optarg, "green")!=0 && strcmp(optarg, "red")!=0){
                    printf( "Аргумент не цвет: 'blue', 'green', 'red'!\n");
                    exit(40);
                }
                strcpy(arg_f2[0], optarg); //2.0
                break;
            case 'r':
            case 't': //радиус, толщина , цвет в 2й функции, длина стороны квадрата, угол поворота изображения
            case 'v':
            case 'a':
            case 'l':
                //printf("%s\n", optarg);
                if (optarg[0] == '-' && optarg[1]=='-'){
                    printf( "Аргумент пропущен!\n");
                    exit(40);
                }
                int j;
                if (optarg[0] == '-') j=1;
                else j=0;
                for (j;j<strlen(optarg);j++){
                    if (!isdigit(optarg[j])){
                        printf( "Аргумент не число!\n");
                        exit(40);
                    }
                }
                if (atoi(optarg)<=0){
                    printf("Аргумент должен быть больше 0!\n");
                    exit(40);
                }
                if (opt=='v') {
                    if (atoi(optarg) > 255 || atoi(optarg) < 0) {
                        printf("Аргумент вне диапазона RGB!\n");
                        exit(40);
                    }
                    strcpy(arg_f2[1], optarg); //2.1
                }
                else if(opt=='r'){
                    strcpy(arg_f4[1], optarg); //4.1
                }
                else if(opt=='a'){
                    if (atoi(optarg)!=90 && atoi(optarg)!=270 && atoi(optarg)!=180){
                        printf( "Угол может быть только: 90, 180, 270!\n");
                        exit(40);
                    }
                    strcpy(arg_f3[2], optarg); //3.2
                }
                else if(opt=='l') strcpy(arg_f1[1], optarg); //1.1
                else{
                    strcpy(thickness, optarg); //1.2, 4.2
                }
                break;
            default:
                printf("Несуществующий параметр или данный параметр не ожидался: %s!\n", argv[optind-1]);
                exit(40);
        }
    };
    //char name[50] = "/home/nikita/Загрузки/Lake.bmp";
    if (strlen(name)==2) strcat(name, argv[argc-1]);
    BmpFileHeader* ls = (BmpFileHeader*)malloc(sizeof(BmpFileHeader));
    BmpInfoHeader* rb = (BmpInfoHeader*)malloc(sizeof(BmpInfoHeader));
    Rgb** our = read_bmp(name, ls, rb);
    if (flag==7) help();
    else if(flag==6){
        info_printer(ls, rb);
    }
    else if (flag==2){
        for (int i=0; i<2;i++){
            if (arg_f2[i][0]=='\0'){
                printf("Не все аргументы переданы для работы с флагом rgbfilter!\n");
                exit(40);
            }
        }
        int col=-1;
        if (strcmp(arg_f2[0], "blue")==0) col=0;
        else if (strcmp(arg_f2[0], "green")==0) col=1;
        else col=2;
        changer_color(our, col, atoi(arg_f2[1]), rb->width, rb->height);
    }
    else if(flag==3){
        if (strlen(left_up)!=0) strcpy(arg_f3[0], left_up);
        for (int i=0; i<3;i++){
            if (arg_f3[i][0]=='\0'){
                printf("Не все аргументы переданы для работы с флагом rotate!\n");
                exit(40);
            }
        }
        int x_l, y_l, x_r, y_r;
        sscanf(arg_f3[0], "%d.%d", &x_l, &y_l);
        sscanf(arg_f3[1], "%d.%d", &x_r, &y_r);
        rotate(our, atoi(arg_f3[2]), &(rb->height), &(rb->width), x_l, y_l, x_r, y_r);
    }
    else if(flag==1){
        if (strlen(left_up)!=0) strcpy(arg_f1[0], left_up);
        if (strlen(color)!=0) strcpy(arg_f1[3], color);
        if (strlen(thickness)!=0) strcpy(arg_f1[2], thickness);
        if (fill_flag==1){
            if (strlen(fill_color)!=0) strcpy(arg_f1[5], fill_color);
            else{
                printf("Не все аргументы переданы для работы с флагом squared_lines!\n");
                exit(40);
            }
        }
        for (int i=0; i<4;i++){
            if (arg_f1[i][0]=='\0'){
                printf("Не все аргументы переданы для работы с флагом squared_lines!\n");
                exit(40);
            }
        }
        int x_ll, y_ll;
        sscanf(arg_f1[0], "%d.%d", &x_ll, &y_ll);
        draw_square(our, x_ll, y_ll, arg_f1[3], atoi(arg_f1[1]), atoi(arg_f1[2]), fill_flag, rb->height, rb->width, arg_f1[5]);
    }
    else if (flag==4){
        if (strlen(color)!=0) strcpy(arg_f4[3], color);
        if (strlen(thickness)!=0) strcpy(arg_f4[2], thickness);
        if (fill_flag==1){
            if (strlen(fill_color)!=0) strcpy(arg_f4[5], fill_color);
            else{
                printf("Не все аргументы переданы для работы с флагом circle!\n");
                exit(40);
            }
        }
        for (int i=0; i<4;i++){
            //printf("[%s]\n", arg_f4[i]);
            if (arg_f4[i][0]=='\0'){
                printf("Не все аргументы переданы для работы с флагом circle!\n");
                exit(40);
            }
        }
        draw_circle(our, arg_f4[0], atoi(arg_f4[1]), arg_f4[3], atoi(arg_f4[2]), fill_flag, rb->height, rb->width, arg_f4[5]);
    }
    //
    FILE* new_bmp = fopen(file_outname, "wb");
    fwrite(ls, 1, sizeof(BmpFileHeader), new_bmp);
    fwrite(rb, 1, sizeof(BmpInfoHeader), new_bmp);
    for (int i = 0; i < rb->height; i++) {
        fwrite(our[i], sizeof(Rgb), rb->width, new_bmp);
    }
    fclose(new_bmp);
    for (int i=0; i<6; i++){
        free(arg_f1[i]);
        free(arg_f4[i]);
    }
    free(arg_f1);
    free(arg_f4);
    for (int i=0; i<2; i++){
        free(arg_f2[i]);
    }
    free(arg_f2);
    for (int i=0; i<3; i++){
        free(arg_f3[i]);
    }
    free(arg_f3);
    free_bmp(ls, rb, our);
}

