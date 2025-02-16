#include <call.h>

bool slim = true;

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    unsigned char v = abs(world_pos.x + world_pos.y * 2 + world_pos.z + 14);
    v *= v;
    *inner = color{.r = (unsigned char)(255 - v), .g = (unsigned char)(v * v), .b = (unsigned char)(v * v * v), .a = 255};
}