#pragma once
// #include <cmath>

#include <math.h>

#include <FastNoiseLite.h>

enum DIRECTION {//assuming were looking at them from front      NOT FROM CHARACTER POV
    LEFT,
    RIGHT,
    UP,
    DOWN,
    FRONT,
    BACK
};

enum PART {//CHARACTER POV
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

struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

color c(int r, int g, int b, int a);

double distance(double x1, double y1, double z1, double x2, double y2, double z2);

double direction_difference(double x1, double y1, double z1, double dx, double dy, double dz, double x2, double y2, double z2);

color spectrum(double zone);

bool is_exposed(DIRECTION dir, PART part, ivec2 plane_pos_for_head_bottom);