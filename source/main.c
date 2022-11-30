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

#define RAD_CHECK 2

const char* chars = " `'.^~_\",-:;\\/!|*+()=><7[]1?il{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM{}rtIvjJcu3znoL25Yf4sCVx&a0Teh96FyZwkUP$ODS@8XbGAgdKmREHpqNB#WQM#WQM#WQM#WQM#WQM#WQM";
// const char* chars = " `*O@#";
//    const char* chars = " oO0@$";


int min(int a, int b) {
    return a < b ? a : b;
}


void main(void){
    if(SIZE>=LIMIT)
        exit(-1);
    
    _Bool ***donut = calloc(sizeof(void*), SIZE);
    uint8_t ***screen = calloc(sizeof(void*), SIZE);
    double dist;
    int i, j, k;
    int l, m, n;
    for(i=0; i<SIZE; i++){
        donut[i] = calloc(sizeof(void*), SIZE);
        screen[i] = calloc(sizeof(void*), SIZE);
        for(j=0; j<SIZE; j++){
            donut[i][j] = calloc(sizeof(_Bool), SIZE);
            screen[i][j] = calloc(sizeof(uint8_t), SIZE);
            for(k=0; k<SIZE; k++){
                dist = sqrt(i*i+j*j+2*SIZE/2*(SIZE/2-i-j));
                donut[i][j][k] = sqrt((dist-SIZE/SHORTNESS)*(dist-SIZE/SHORTNESS)+(k-SIZE/2)*(k-SIZE/2))<=SIZE/SLIMNESS;
                    // if(l+k<SIZE && l+k>=0 && donut[i][j][k+l])
                    //     screen[i][j][k]++;
            }
        }
    }
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            for(k=0; k<SIZE; k++){
                for(l=-RAD_CHECK; l<=RAD_CHECK; l++){
                    for(m=-RAD_CHECK; m<=RAD_CHECK; m++){
                        for(n=-RAD_CHECK; n<=RAD_CHECK; n++){
                            if(i+l<SIZE && i+l>=0 && j+m<SIZE && j+m>=0 && k+n<SIZE && k+n>=0 && donut[i+l][j+m][k+n])
                                screen[i][j][k]++;
                        }
                    }
                }
            }
        }
    }
    for(i=0; i<SIZE; i++, usleep(SLEEP_uS), printf("\033[2J\033[1;1H"))
        for(j = 0; j<SIZE; j++, printf("|\n"))
            for(k = 0; k<SIZE; k++) 
                printf(" %c ", chars[screen[j][k][i]]);
    for(i=0; i<SIZE; i++, usleep(SLEEP_uS), printf("\033[2J\033[1;1H"))
        for(j = 0; j<SIZE; j++, printf("|\n"))
            for(k = 0; k<SIZE; k++) 
                printf(" %c ", chars[screen[i][j][k]+screen[i][k][j]+screen[j][k][i]]);
}