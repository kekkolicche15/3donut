void* calloc(), usleep();
int printf(const char*, ...);
double sqrt(double);

#define SIZE 200UL

#define SHORTNESS 4
#define SLIMNESS 10

#define SLEEP_uS 40000

void main(void){
    _Bool ***donut = calloc(sizeof(void*), SIZE);
    int dist;
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
    
    for(i=0; i<SIZE; i++, usleep(SLEEP_uS), printf("\033[2J\033[1;1H"))
        for(j = 0; j<SIZE; j++, printf("|\n"))
            for(k = 0; k<SIZE; k++) 
                printf(" %c ", donut[j][k][i] ? '0' : ' ');
    for(i=0; i<SIZE; i++, usleep(SLEEP_uS), printf("\033[2J\033[1;1H"))
        for(j = 0; j<SIZE; j++, printf("|\n"))
            for(k = 0; k<SIZE; k++)
                printf(" %c ", donut[i][k][j]||donut[i][j][k] ? '0' : ' ');
}
