#pragma once

#include <FastNoiseLite.h>

#include <cmath>

extern bool slim;

struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

enum DIRECTION {//assuming were looking at them from front      NOT FROM CHARACTER POV
    LEFT,
    RIGHT,
    UP,
    DOWN,
    FRONT,
    BACK
};

enum PART {
    HEAD,
    CHEST,
    LEFT_ARM,
    RIGHT_ARM,
    LEFT_LEG,
    RIGHT_LEG
};

struct ivec2 {
    int x;
    int y;
};

struct ivec3 {
    int x;
    int y;
    int z;
};

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part);