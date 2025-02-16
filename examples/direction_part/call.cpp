#include <call.h>

bool slim = true;

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    switch (dir){
        case LEFT:
            *inner = color{.r = 0, .g = 0, .b = 255, .a = 255};
            break;
        case RIGHT:
            *inner = color{.r = 255, .g = 0, .b = 255, .a = 255};
            break;
        case UP:
            *inner = color{.r = 0, .g = 255, .b = 0, .a = 255};
            break;
        case DOWN:
            *inner = color{.r = 255, .g = 0, .b = 0, .a = 255};
            break;
        case FRONT:
            *inner = color{.r = 255, .g = 255, .b = 0, .a = 255};
            break;
        case BACK:
            *inner = color{.r = 0, .g = 255, .b = 255, .a = 255};
            break;
    }
    if ((plane_pos.x + plane_pos.y) % 2){
        switch (part){
            case HEAD:
                *outer = color{.r = 255, .g = 0, .b = 0, .a = 255};
                break;
            case CHEST:
                *outer = color{.r = 0, .g = 255, .b = 0, .a = 255};
                break;
            case LEFT_ARM:
                *outer = color{.r = 0, .g = 0, .b = 255, .a = 255};
                break;
            case RIGHT_ARM:
                *outer = color{.r = 255, .g = 0, .b = 255, .a = 255};
                break;
            case LEFT_LEG:
                *outer = color{.r = 255, .g = 255, .b = 0, .a = 255};
                break;
            case RIGHT_LEG:
                *outer = color{.r = 0, .g = 255, .b = 255, .a = 255};
                break;
        }
    }
}