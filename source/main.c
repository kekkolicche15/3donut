void* calloc(), usleep(), exit();
int printf(const char*, ...);
double sqrt(double);

#define SIZE 200UL
#define LIMIT 256

#define SHORTNESS 4
#define SLIMNESS 10

#define SLEEP_uS 40000

typedef unsigned char uint8_t;
typedef char int8_t;

#define RAD_CHECK 1

const char* chars = " `'.^~_\",-:;\\/!|*+()=><7[]1?il{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM";
int i, j, k;
int l, m, n; //suqqiami lo scroto best practices

void printDonut(uint8_t*** donut){
    for(i=0; i<SIZE; i++, usleep(SLEEP_uS), printf("\033[2J\033[1;1H"))
        for(j = 0; j<SIZE; j++, printf("|\n"))
            for(k = 0; k<SIZE; k++) 
                printf(" %c ", chars[donut[j][k][i]]);
}

int min(int a, int b) {
    return a < b ? a : b;
}



void main(void){
    if(SIZE>=LIMIT)
        exit(-1);
    _Bool ***donut = calloc(sizeof(void*), SIZE);
    uint8_t ***screen = calloc(sizeof(void*), SIZE);
    double dist;
    for(i=0; i<SIZE; i++){
        donut[i] = calloc(sizeof(void*), SIZE);
        screen[i] = calloc(sizeof(void*), SIZE);
        for(j=0; j<SIZE; j++){
            donut[i][j] = calloc(sizeof(_Bool), SIZE);
            screen[i][j] = calloc(sizeof(uint8_t), SIZE);
            for(k=0; k<SIZE; k++){
                dist = sqrt(i*i+j*j+2*SIZE/2*(SIZE/2-i-j));
                donut[i][j][k] = sqrt((dist-SIZE/SHORTNESS)*(dist-SIZE/SHORTNESS)+(k-SIZE/2)*(k-SIZE/2))<=SIZE/SLIMNESS;
            }
        }
    }

    uint8_t ***prefix = calloc(sizeof(void*), SIZE + RAD_CHECK * 2 + 1);
    for (int i = 0; i < SIZE + RAD_CHECK * 2 + 1; i++) {
        prefix[i] = calloc(sizeof(void*), SIZE + RAD_CHECK * 2 + 1);
        for (int j = 0; j < SIZE + RAD_CHECK * 2 + 1; j++) {
            prefix[i][j] = calloc(sizeof(uint8_t), SIZE + RAD_CHECK * 2 + 1);
        }
    }

    for (int i = 0; i < SIZE + RAD_CHECK * 2 + 1; i++) {
        for (int j = 0; j < SIZE + RAD_CHECK * 2 + 1; j++) {
            for (int k = 0; k < SIZE + RAD_CHECK * 2 + 1; k++) {
                if (i <= RAD_CHECK || j <= RAD_CHECK || k <= RAD_CHECK ) {
                    prefix[i][j][k] = 0;
                } else {
                    if (i > SIZE + RAD_CHECK || j > SIZE + RAD_CHECK || k > SIZE + RAD_CHECK) {
                        prefix[i][j][k] = 0;
                    } else {
                        prefix[i][j][k] = donut[i-RAD_CHECK-1][j-RAD_CHECK-1][k-RAD_CHECK-1];
                    }
                    prefix[i][j][k] += prefix[i-1][j][k] + prefix[i][j-1][k] + prefix[i][j][k-1] - prefix[i-1][j-1][k] - prefix[i-1][j][k-1] - prefix[i][j-1][k-1] + prefix[i-1][j-1][k-1];
                }
            } 
        }
    }
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            for (int k = 0; k < SIZE; k++) 
                screen[i][j][k] = prefix[i+2*RAD_CHECK+1][j+2*RAD_CHECK+1][k+2*RAD_CHECK+1] 
                                    - prefix[i][j+2*RAD_CHECK+1][k+2*RAD_CHECK+1] 
                                    - prefix[i+2*RAD_CHECK+1][j][k+2*RAD_CHECK+1] 
                                    - prefix[i+2*RAD_CHECK+1][j+2*RAD_CHECK+1][k] 
                                    + prefix[i][j][k+2*RAD_CHECK+1] 
                                    + prefix[i][j+2*RAD_CHECK+1][k] 
                                    + prefix[i+2*RAD_CHECK+1][j][k] 
                                    - prefix[i][j][k];
    
    for(i=0; i<SIZE; i++, usleep(SLEEP_uS), printf("\033[2J\033[1;1H"))
        for(j = 0; j<SIZE; j++, printf("|\n"))
            for(k = 0; k<SIZE; k++) 
                printf(" %c ", chars[screen[i][j][k]+screen[i][k][j]+screen[j][k][i]]);

    printDonut(screen);
}
/*

    TODO 
    printDonut(donut, 1, 1, 1, +, +, +, |, |);
    void printDonut(uint8_t*** donut){
        for(i=0; i<SIZE; i++, usleep(SLEEP_uS), printf("\033[2J\033[1;1H"))
            for(j = 0; j<SIZE; j++, printf("|\n"))
                for(k = 0; k<SIZE; k++) 
                    printf(" %c ", chars[expr(donut[i][j][k], donut[i][k][j], donut[j][k][i])]);
    }
*/