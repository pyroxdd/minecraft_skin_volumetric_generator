#include <call.h>

bool slim = true;

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    unsigned char c = (world_pos.x + world_pos.y + world_pos.z + 1000) % 2 * 255;
    *inner = color{.r = c, .g = c, .b = c, .a = 255};
}