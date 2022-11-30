void* calloc();
int usleep();
long write();
double sqrt(double);

#define SIZE 128
#define SIZE_UL (unsigned long)SIZE
#define HALF (SIZE/2)


#define SHORTNESS 4
#define SLIMNESS 10

void main(void){
    _Bool ***donut = calloc(sizeof(void*), SIZE_UL);
    double dist;
    int i, j, k;
    for(i=0; i<SIZE; i++){
        donut[i] = calloc(sizeof(void*), SIZE_UL);
        for(j=0; j<SIZE; j++){
            donut[i][j] = calloc(sizeof(_Bool), SIZE_UL);
            for(k=0; k<SIZE; k++){
                dist = sqrt(i*i+j*j+2*HALF*(HALF-i-j));
                donut[i][j][k] = sqrt((dist-SIZE*1./SHORTNESS)*(dist-SIZE*1./SHORTNESS)+(k-HALF)*(k-HALF))<=SIZE*1./SLIMNESS;
            }
        }
    }
    
    for(int i=0; i<SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) 
                write(1, donut[j][k][i]?" 0":"  ", 2);
            write(1, "|\n", 2);
        }
        usleep(70000);
        for (int k = 0; k < SIZE; k++)
            write(1, "\n", 2);
    }
    for(int i=0; i<SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++)
                write(1, donut[i][k][j]||donut[i][j][k]?" # ":"  ", 2);
            write(1, "|\n", 2);
        }
        usleep(70000);
        for (int k = 0; k < SIZE; k++) 
            write(1, "\n", 2);
    }
}