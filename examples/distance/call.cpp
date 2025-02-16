#include <call.h>

bool slim = true;

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    double v = distance(world_pos.x, world_pos.y, world_pos.z, 3, -9, -20);
    double iv = pow((sin(v) + 1) / 2, 6) * 255;
    double swap = 1 - pow(v / 25, 3);
    *inner = color{.r = (unsigned char)(iv), .g = (unsigned char)(iv * swap + 255 * (1 - swap)), .b = (unsigned char)(iv * swap + 255 * (1 - swap)), .a = 255};
    double ov = 5 - v;
    if (ov < 0) ov = 0;
    else {
        ov *= 25;
        *outer = color{.r = (unsigned char)(255), .g = (unsigned char)(127 + (1 - pow(1 - ov / 255, 3)) * 127), .b = (unsigned char)(ov), .a = 255};
    }
}