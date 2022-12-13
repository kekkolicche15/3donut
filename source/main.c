void *calloc(), usleep(), free(void*);
int printf(const char *, ...);
double sqrt(double);
double cos(double);
double sin(double);
double round(double);

typedef unsigned char uint8_t;

const char *symbols = "MQW#BNqpHERmKdgAGbX8@SDO$PUkwZyF69heT0a&xVCs4fY52Lonz3ucJjvItr}{li?1][7<>=)(+*|!/\\;:-,\"_~^.'`";
const int symbols_size = 94;
const double PI = 3.141592653589793;

const unsigned long SIZE = 100;
const int NPOINTS = 200;
const int R1 = 25;
const int R2 = 10;
const int SLEEP_uS = 17000;

// --------------------

int min(int a, int b) {
    return a < b ? a : b;
}

struct point
{
    double x, y, z;
};

struct angle3d
{
    double x, y, z;
};

// ruota di angle attorno all'asse x
struct point xrotate(struct point p, double theta)
{
    struct point q = p;
    q.y = p.y * cos(theta) - p.z * sin(theta);
    q.z = p.y * sin(theta) + p.z * cos(theta);
    return q;
}

struct point yrotate(struct point p, double theta)
{
    struct point q = p;
    q.x = p.x * cos(theta) + p.z * sin(theta);
    q.z = -p.x * sin(theta) + p.z * cos(theta);
    return q;
}

struct point zrotate(struct point p, double theta)
{
    struct point q = p;
    q.x = p.x * cos(theta) - p.y * sin(theta);
    q.y = p.x * sin(theta) + p.y * cos(theta);
    return q;
}

struct point rotate(struct point p, struct angle3d theta)
{
    p = xrotate(p, theta.x);
    p = yrotate(p, theta.y);
    p = zrotate(p, theta.z);
    return p;
}

struct angle3d to_radians(struct angle3d *theta)
{
    theta->x = theta->x * 2 * PI / 360;
    theta->y = theta->y * 2 * PI / 360;
    theta->z = theta->z * 2 * PI / 360;
}

struct point get_torus(double u, double v) {
    struct point p = {(R1 + R2 * cos(v)) * cos(u), (R1 + R2 * cos(v)) * sin(u), R2 * sin(v)};
    return p;
}

double dist(struct point p) {
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

void print_matrix(uint8_t **mat, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf(" %c ", mat[i][j] ? symbols[mat[i][j] - 1] : ' ');
        }
        printf("|\n");
    }
    printf("\033[2J\033[1;1H");
}

// --------------------

int main(void) {
    // alloca la ciambella
    uint8_t** donut = calloc(SIZE, sizeof(uint8_t*));
    for (int i = 0; i < SIZE; i++) {
        donut[i] = calloc(SIZE, sizeof(uint8_t));
    }

    const double maxdist = (double) SIZE * 1.118033988749895;

    struct angle3d theta = {0., 0., 0.};
    while (1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                donut[i][j] = 0;
            }
        }

        for (int i = 0; i < NPOINTS; i++) {
            for (int j = 0; j < NPOINTS; j++) {
                struct point p = rotate(get_torus((double) i / NPOINTS * 2 * PI, (double) j / NPOINTS * 2 * PI), theta);
                donut[((int) round(p.x)) + SIZE / 2][((int) round(p.y)) + SIZE / 2] = min((int) (dist(p) / maxdist * ((double) symbols_size)), symbols_size - 1);
            }
        }

        printf("\033[2J\033[1;1H");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf(" %c ", donut[i][j] ? symbols[donut[i][j]] : ' ');
            }
            printf("\n");
        }

        theta.x += 0.05;
        theta.y -= 0.04;
        theta.z += 0.08;
        usleep(SLEEP_uS);
    }

    // dealloca la ciambella
    for (int i = 0; i < SIZE; i++) {
        free(donut[i]);
    }
    free(donut);

    return 0;
}
