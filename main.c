#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
double sqrt(double __x);


#define SIZE 300
#define HALF (SIZE/2)
#define SHORTNESS 4
#define THICKNESS 10


int main(int argc, char**argv){
    _Bool ***donut = calloc(sizeof(void*), SIZE);
    for(int i=0; i<SIZE; i++){
        donut[i] = calloc(sizeof(void*), SIZE);
        for(int j=0; j<SIZE; j++){
            donut[i][j] = calloc(sizeof(_Bool), SIZE);
            for(int k=0; k<SIZE; k++){
                double x = i-HALF;
                double y = j-HALF;
                double z = k-HALF;
                double dist = sqrt(x*x+y*y);
                x = dist;
                y = 0.;
                dist = sqrt((x-SIZE*1./SHORTNESS)*(x-SIZE*1./SHORTNESS)+z*z);
                donut[i][j][k] = dist<=SIZE*1./THICKNESS;
            }
        }
    }
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++)
            printf("%c", donut[i][j][HALF]?'*':'.');
        printf("\n");
    }
    printf("\n");
    printf("\n");
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++)
            printf("%c", donut[HALF][i][j]?'*':'.');
        printf("\n");
    }
    printf("\n");
    printf("\n");
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++)
            printf(" %c ", donut[i][HALF][j]?'#':' ');
        printf("\n");
    }

    printf("\n");
    printf("\n");
    for(int i=0; i<SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                printf(" %c ", donut[j][k][i]?'*':'.');
            }
            printf("\n");
        }
        usleep(20000);
        for(int l=0; l<300;l++)
            printf("\n");
    }
    for(int i=0; i<SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                printf(" %c ", donut[i][k][j]||donut[i][j][k]?'#':' ');
            }
            printf("|\n");
        }
        usleep(20000);
        for(int l=0; l<300;l++)
            printf("\n");
    }

    return 0;
}