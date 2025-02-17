#include <helper.h>

#include <stdio.h>//????????????????

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

double magnitude(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

void cross_product(double ax, double ay, double az, double bx, double by, double bz, double &cx, double &cy, double &cz) {
    cx = ay * bz - az * by;
    cy = az * bx - ax * bz;
    cz = ax * by - ay * bx;
}

double direction_difference(double x1, double y1, double z1, double dx, double dy, double dz, double x2, double y2, double z2) {
    double vx = x2 - x1;
    double vy = y2 - y1;
    double vz = z2 - z1;
    
    double cx, cy, cz;
    cross_product(dx, dy, dz, vx, vy, vz, cx, cy, cz);
    
    return magnitude(cx, cy, cz) / magnitude(dx, dy, dz);
}

// double myfmod(double a, double b){
//     return a - b * floor(a / b);
// }
// double cut1(double a){
//     if (a > 1) return 1;
//     else if (a < 0) return 0;
//     else return a;
// }

// color spectrum(double zone){// 0 - 1
//     // printf("%f\n", fmod(10, 2.5));
//     // printf("%f\n", fmod(1, 0.2));
//     // printf("%f\n", fmod(2, 0.7));
//     // getchar();
//     zone *= -2;//-4.5;
//     return color{
//         .r = (unsigned char)(cut1(abs((fmod(zone, 2) - 1) * 3) - 1) * 255),
//         .g = (unsigned char)(cut1(abs((fmod(zone + 2.0/3.0, 2) - 1) * 3) - 1) * 255),
//         .b = (unsigned char)(cut1(abs((fmod(zone + 4.0/3.0, 2) - 1) * 3) - 1) * 255),
//         .a = 255
//     };
// }

double cut1(double a){
    if (a > 1) return 1;
    else if (a < 0) return 0;
    else return a;
}

double myfmod(double a, double b){
    return a - b * floor(a / b);
}

color spectrum(double zone){// 0 - 1
    zone *= -2;//-4.5;
    return color{
            .r = (unsigned char)(cut1(abs((myfmod(zone, 2.0) - 1) * 3) - 1) * 255),
            .g = (unsigned char)(cut1(abs((myfmod(zone + 2/3.0, 2.0) - 1) * 3) - 1) * 255),
            .b = (unsigned char)(cut1(abs((myfmod(zone + 4/3.0, 2.0) - 1) * 3) - 1) * 255),
            .a = 255
        };
}

bool is_exposed(DIRECTION dir, PART part, ivec2 plane_pos_for_head_bottom){
    switch (part){
        case HEAD:
            if (dir == DOWN && plane_pos_for_head_bottom.y >= 2 && plane_pos_for_head_bottom.y <= 5) return false;
            else return true;
        case CHEST:
            switch (dir){
                case LEFT:
                case RIGHT:
                case UP:
                case DOWN:
                    return false;
                default:
                    return true;
            }
        case LEFT_ARM:
            switch (dir){
                case LEFT:
                    return false;
                default:
                    return true;
            }
        case RIGHT_ARM:
            switch (dir){
                case RIGHT:
                    return false;
                default:
                    return true;
            }
        case LEFT_LEG:
            switch (dir){
                case UP:
                case LEFT:
                    return false;
                default:
                    return true;
            }
        case RIGHT_LEG:
            switch (dir){
                case UP:
                case RIGHT:
                    return false;
                default:
                    return true;
            }
    }
}

color c(int r, int g, int b, int a){
    return color{.r = (unsigned char)(r), .g = (unsigned char)(g), .b = (unsigned char)(b), .a = (unsigned char)(a)};
}