#include <call.h>

bool slim = true;

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    if (plane_pos.x == 0 || plane_pos.y == 0 || plane_pos.x == plane_size.x - 1 || plane_pos.y == plane_size.y - 1){
        *inner = color{.r = 255, .g = 255, .b = 255, .a = 255};
        *outer = color{.r = 255, .g = 255, .b = 0, .a = 255};
    }
}