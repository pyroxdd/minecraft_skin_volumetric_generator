#include <call.h>

bool slim = true;

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    double v = distance(world_pos.x, world_pos.y, world_pos.z, 0, 8, -16);
    // if ((int)(v) % 8 < 2) v = 0;
    // else v = 255;
    double iv = pow((sin(v) + 1) / 2, 4) * 255;
    *inner = color{.r = (unsigned char)(iv), .g = (unsigned char)(iv), .b = (unsigned char)(iv * 0.9 + 25), .a = 255};
    double ov = 9 - v;
    if (ov < 0) ov = 0;
    else {
        ov *= 25;
        *outer = color{.r = (unsigned char)(255), .g = (unsigned char)(127 + (1 - pow(1 - ov / 255, 3)) * 127), .b = (unsigned char)(ov), .a = 255};
    }
}