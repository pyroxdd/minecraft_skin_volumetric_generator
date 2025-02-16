#include <call.h>

bool slim = true;

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    double v = world_pos.x + world_pos.y * 2 + world_pos.z + 14;
    
    if (v < 0){
        v *= -1;
        unsigned char z = 0;
        if (v > 10) z = v * v * v * 4.7 - 10;
        *inner = color{.r = (unsigned char)(v * v * v), .g = z, .b = (unsigned char)(v * v), .a = 255};
        if ((unsigned char)(v * v * v) > 46 && (unsigned char)(v * v * v) < 57) *outer = color{.r = (unsigned char)(v * v * v * v * v * v * v * v), .g = (unsigned char)(v * v * v * v), .b = (unsigned char)(v * v * v * v * v), .a = 255};
    } else {
        unsigned char z = 0;
        if (v > 10) z = v * v * v * 6.1 - 10;
        *inner = color{.r = z, .g = (unsigned char)(v * v), .b = (unsigned char)(v * v * v), .a = 255};
        if ((unsigned char)(v * v * v * v * v * v * v) > 220 || ((unsigned char)(v * v * v * v * v * v * v) < 128 && (unsigned char)(v * v * v * v * v * v * v) > 100)) *outer = color{.r = (unsigned char)(255 - v * v * v * -982.736), .g = (unsigned char)(192 + v * v * v * 13.7), .a = 255};
    }
}