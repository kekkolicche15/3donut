void* calloc(), usleep();
int printf(const char*, ...);
double sqrt(double);

#define SIZE 250UL

#define SHORTNESS 4
#define SLIMNESS 10

void main(void){
    _Bool ***donut = calloc(sizeof(void*), SIZE);
    double dist;
    int i, j, k;
    for(i=0; i<SIZE; i++){
        donut[i] = calloc(sizeof(void*), SIZE);
        for(j=0; j<SIZE; j++){
            donut[i][j] = calloc(sizeof(_Bool), SIZE);
            for(k=0; k<SIZE; k++){
                dist = sqrt(i*i+j*j+2*SIZE/2*(SIZE/2-i-j));
                donut[i][j][k] = sqrt((dist-SIZE*1./SHORTNESS)*(dist-SIZE/SHORTNESS)+(k-SIZE/2)*(k-SIZE/2))<=SIZE/SLIMNESS;
            }
        }
    }
    
    for(int i=0; i<SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) 
                printf(" %c ", donut[j][k][i] ? '0' : ' ');
            printf("|\n");
        }
        usleep(40000);
        printf("\033[2J\033[1;1H"); //ansi terminal only
    }
    for(int i=0; i<SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++)
                printf(" %c ", donut[i][k][j]||donut[i][j][k] ? '0' : ' ');
            printf("|\n");
        }
        usleep(40000);
        printf("\033[2J\033[1;1H"); //ansi terminal only
    }
}
