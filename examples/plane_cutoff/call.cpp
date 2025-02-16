#include <call.h>

bool slim = true;

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    unsigned char v = abs(world_pos.x + world_pos.y * 2 + world_pos.z + 15);
    if (v < 10) v = 0;
    else v = 255;
    *inner = color{.r = v, .g = v, .b = v, .a = 255};
}