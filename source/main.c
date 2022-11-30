void* calloc(), usleep();
int printf(const char*, ...);
double sqrt(double);
double cos(double);
double sin(double);

#define SIZE 100UL

#define SHORTNESS 4
#define SLIMNESS 10

#define SLEEP_uS 100000

#define PI 3.141592653589793

struct point {
    double x, y, z;
};

struct angle3d {
    double x, y, z;
};

// ruota di angle attorno all'asse x
struct point xrotate(struct point p, double theta) {
    struct point q = p;
    q.y = p.y * cos(theta) - p.z * sin(theta);
    q.z = p.y * sin(theta) + p.z * cos(theta);
    return q;
}

struct point yrotate(struct point p, double theta) {
    struct point q = p;
    q.x = p.x * cos(theta) + p.z * sin(theta);
    q.z = -p.x * sin(theta) + p.z * cos(theta);
    return q;
}

struct point zrotate(struct point p, double theta) {
    struct point q = p;
    q.x = p.x * cos(theta) - p.y * sin(theta);
    q.y = p.x * sin(theta) + p.y * cos(theta);
    return q;
}

struct point rotate(struct point p, struct angle3d theta) {
    p = xrotate(p, theta.x);
    p = yrotate(p, theta.y);
    p = zrotate(p, theta.z);
    return p;
}

struct angle3d to_radians(struct angle3d theta) {
    theta.x = theta.x * 2 * PI / 360;
    theta.y = theta.y * 2 * PI / 360;
    theta.z = theta.z * 2 * PI / 360;
}

void print_matrix(_Bool **mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf(" %c ", mat[i][j] ? '0' : ' ');
        }
        printf("|\n");
    }
    printf("\033[2J\033[1;1H");
}

_Bool in_torus(struct point p) {
    double dist = sqrt(p.x*p.x+p.y*p.y);
    p.x = dist;
    p.y = 0.;
    dist = sqrt((p.x-SIZE*1./SHORTNESS)*(p.x-SIZE*1./SHORTNESS)+p.z*p.z);
    return dist <= SIZE * 1. / SLIMNESS;
}

int main(void){
    /*
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
    
    for(i=0; i<SIZE; i++, usleep(SLEEP_uS), printf("\033[2J\033[1;1H"))
        for(j = 0; j<SIZE; j++, printf("|\n"))
            for(k = 0; k<SIZE; k++) 
                printf(" %c ", donut[j][k][i] ? '0' : ' ');
    for(i=0; i<SIZE; i++, usleep(SLEEP_uS), printf("\033[2J\033[1;1H"))
        for(j = 0; j<SIZE; j++, printf("|\n"))
            for(k = 0; k<SIZE; k++)
                printf(" %c ", donut[i][k][j]||donut[i][j][k] ? '0' : ' ');
    */

    _Bool ***donut = calloc(sizeof(void*), SIZE);
    for(int i=0; i<SIZE; i++){
        donut[i] = calloc(sizeof(void*), SIZE);
        for(int j=0; j<SIZE; j++){
            donut[i][j] = calloc(sizeof(_Bool), SIZE);
        }
    }

    _Bool **grid = calloc(sizeof(void*), SIZE);
    for (int i = 0; i < SIZE; i++) {
        grid[i] = calloc(sizeof(_Bool), SIZE);
    }

    struct angle3d theta = {0., 0., 0.};

    while (1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    struct point p;
                    p.x = (double) i - SIZE / 2;
                    p.y = (double) j - SIZE / 2;
                    p.z = (double) k - SIZE / 2;

                    p = rotate(p, theta);

                    grid[i][j] |= in_torus(p);
                    //donut[i][j][k] = in_torus(p);
                }
            }
        }

        print_matrix(grid, SIZE, SIZE);

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                grid[i][j] = 0;
            }
        }

        theta.x += 0.35;
        theta.y += 0.35;
        theta.z += 0.35;

        usleep(SLEEP_uS);
    }

    return 0;
}
