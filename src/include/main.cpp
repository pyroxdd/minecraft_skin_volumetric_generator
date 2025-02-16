#include <stdio.h>
#include <write.h>
#include <vector>

#include <cmath>

#include <FastNoiseLite.h>

#define SIZE 64
color pixels[SIZE * SIZE];

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

struct plane {
    ivec2 size;
    ivec3 position;
    ivec2 inner_destination;
    ivec2 outer_destination;
    DIRECTION dir;
    PART part;
};

std::vector<plane> planes;

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

//two point distance integer
// double tpdi(ivec3 a, ivec3 b) {
//     return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
// }

// color dir_to_color(DIRECTION dir){
//     switch (dir){
//         case LEFT:
//             return color{.r = 0, .g = 0, .b = 255, .a = 255};
//         case RIGHT:
//             return color{.r = 255, .g = 0, .b = 255, .a = 255};
//         case UP:
//             return color{.r = 0, .g = 255, .b = 0, .a = 255};
//         case DOWN:
//             return color{.r = 255, .g = 0, .b = 0, .a = 255};
//         case FRONT:
//             return color{.r = 255, .g = 255, .b = 0, .a = 255};
//         case BACK:
//             return color{.r = 0, .g = 255, .b = 255, .a = 255};
//     }
// }

void add_plane(int width, int height, int inner_dest_x, int inner_dest_y, int outer_dest_x, int outer_dest_y, int w_x, int w_y, int w_z, DIRECTION dir, PART part){
    plane p;
    p.size = {.x = width, .y = height};
    p.inner_destination = {.x = inner_dest_x, .y = inner_dest_y};
    p.outer_destination = {.x = outer_dest_x, .y = outer_dest_y};
    p.position = {.x = w_x, .y = w_y, .z = w_z};
    p.dir = dir;
    p.part = part;
    planes.push_back(p);
}

ivec3 world_pos(plane p, int x, int y){
    /*
        x - front axis (from character front to back)
        y - side axis (from character left to right)
        z - vertical axis

        plane origin is always in upper left back corner (character pov)
    */
    ivec3 ret = p.position;
    switch (p.dir){
        case LEFT:
            ret.x += x;
            ret.z -= y;
            break;
        case RIGHT:
            ret.x += p.size.x - x - 1;
            ret.z -= y;
            break;
        case UP:
        case DOWN:
            ret.y += x;
            ret.x += y;
            break;
        case FRONT:
            ret.y += x;
            ret.z -= y;
            break;
        case BACK:
            ret.y += p.size.x - x - 1;
            ret.z -= y;
            break;
    }
    return ret;
}

void a(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    double dist = distance(world_pos.x, world_pos.y, world_pos.z, 0 - 0.5, 0 - 0.5, -12 - 0.5);
    if (int(dist) % 6 < 3) {
        outer->r = 255;
        outer->a = 255;
    }
}

void b(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static FastNoiseLite noise;
    static bool ready = false;
    if (!ready){
        ready = true;
        noise.SetSeed(451937);
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFrequency(0.1f);
    }

    double v = noise.GetNoise(float(world_pos.x), float(world_pos.y), float(world_pos.z));
    if (v > 0.3){
        outer->r = 255;
        outer->g = 255;
        outer->b = 255;
        outer->a = 255;
    }
}

void c(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static FastNoiseLite noise;
    static bool ready = false;
    if (!ready){
        ready = true;
        noise.SetSeed(451937);
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFrequency(0.03f);
    }

    double dv = (noise.GetNoise(float(world_pos.x), float(world_pos.y), float(world_pos.z)) + 1) / 2;
    
    inner->r = 255;
    inner->g = (1 - dv) * 255;
    inner->b = dv * 255;
}

void d(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static FastNoiseLite noise;
    static bool ready = false;
    if (!ready){
        ready = true;
        noise.SetSeed(73458);
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFrequency(0.07f);
    }
    double off_scale = 1;
    double off_x = noise.GetNoise(float(world_pos.x * off_scale + 19972), float(world_pos.y * off_scale + 978913), float(world_pos.z * off_scale + 127630));

    double off_y = noise.GetNoise(float(world_pos.x * off_scale + 786412), float(world_pos.y * off_scale + 45738), float(world_pos.z * off_scale + 768431));

    double off_z = noise.GetNoise(float(world_pos.x * off_scale + 334761), float(world_pos.y * off_scale + 897566), float(world_pos.z * off_scale + 561974));
    double off_mult = 8.3;
    double dv = (noise.GetNoise(float(world_pos.x) + off_x * off_mult, float(world_pos.y) + off_y * off_mult, float(world_pos.z) + off_z * off_mult) + 1) / 2;
    
    inner->r = 255;
    inner->g = (1 - dv) * 255;
    inner->b = dv * 255;

    if (dv < 0.4){
        outer->r = inner->r;
        outer->g = inner->g;
        outer->b = inner->b;
        outer->a = 255;
    }
}

void e(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
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

void f(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    if (plane_pos.x == 0 || plane_pos.y == 0 || plane_pos.x == plane_size.x - 1 || plane_pos.y == plane_size.y - 1){
        *inner = color{.r = 255, .g = 255, .b = 255, .a = 255};
        *outer = color{.r = 255, .g = 255, .b = 0, .a = 255};
    }
}

void g(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    unsigned char v = abs(world_pos.x + world_pos.y * 2 + world_pos.z + 15);
    if (v < 10) v = 0;
    else v = 255;
    *inner = color{.r = v, .g = v, .b = v, .a = 255};
}

void h(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    unsigned char v = abs(world_pos.x + world_pos.y * 2 + world_pos.z + 15) * 9.4;
    if (v < 20) *inner = color{.r = 255, .g = 0, .b = 127, .a = 255};
    else {
        v *= v;
        *inner = color{.r = v, .g = v, .b = v, .a = 255};
    }
}

void i(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    unsigned char v = abs(world_pos.x + world_pos.y * 2 + world_pos.z + 14);
    v *= v;
    *inner = color{.r = (unsigned char)(255 - v), .g = (unsigned char)(v * v), .b = (unsigned char)(v * v * v), .a = 255};
}

void j(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
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

void k(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
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

void test(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
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

void set_plane(plane p){
    for (int x = 0; x < p.size.x; x++){
        for (int y = 0; y < p.size.y; y++){
            ivec2 inner_destination = {.x = x + p.inner_destination.x, .y = y + p.inner_destination.y};
            ivec2 outer_destination = {.x = x + p.outer_destination.x, .y = y + p.outer_destination.y};
            color inner = {.r = 0, .g = 0, .b = 0, .a = 255};
            color outer = {.r = 0, .g = 0, .b = 0, .a = 0};
            test(&inner, &outer, world_pos(p, x, y), ivec2{.x = x, .y = y}, p.size, p.dir, p.part);
            pixels[inner_destination.y * SIZE + inner_destination.x] = inner;
            pixels[outer_destination.y * SIZE + outer_destination.x] = outer;
        }
    }
}

int main( int argc, char *argv[] ){
    printf("hi\n");

    bool slim = true;

    add_plane(8, 8, 8, 0, 40, 0, -4, -4, 0, UP, HEAD);//THEIR HEAD
    add_plane(8, 8, 16, 0, 48, 0, -4, -4, -8, DOWN, HEAD);

    add_plane(8, 8, 0, 8, 32, 8, -4, -4, 0, LEFT, HEAD);
    add_plane(8, 8, 8, 8, 40, 8, 4, -4, 0, FRONT, HEAD);
    add_plane(8, 8, 16, 8, 48, 8, -4, 4, 0, RIGHT, HEAD);
    add_plane(8, 8, 24, 8, 56, 8, -4, -4, 0, BACK, HEAD);

    add_plane(8, 4, 20, 16, 20, 32, -2, -4, -8, UP, CHEST);//THEIR CHEST
    add_plane(8, 4, 28, 16, 28, 32, -2, -4, -20, DOWN, CHEST);

    add_plane(4, 12, 16, 20, 16, 36, -2, -4, -8, LEFT, CHEST);
    add_plane(8, 12, 20, 20, 20, 36, 2, -4, -8, FRONT, CHEST);
    add_plane(4, 12, 28, 20, 28, 36, -2, 4, -8, RIGHT, CHEST);
    add_plane(8, 12, 32, 20, 32, 36, -2, -4, -8, BACK, CHEST);

    if (slim){
        add_plane(3, 4, 36, 48, 52, 48, -2, 4, -8, UP, LEFT_ARM);//THEIR LEFT ARM
        add_plane(3, 4, 39, 48, 55, 48, -2, 4, -20, DOWN, LEFT_ARM);

        add_plane(4, 12, 32, 52, 48, 52, -2, 4, -8, LEFT, LEFT_ARM);
        add_plane(3, 12, 36, 52, 52, 52, 2, 4, -8, FRONT, LEFT_ARM);
        add_plane(4, 12, 39, 52, 55, 52, -2, 7, -8, RIGHT, LEFT_ARM);
        add_plane(3, 12, 43, 52, 59, 52, -2, 4, -8, BACK, LEFT_ARM);

        add_plane(3, 4, 44, 16, 44, 32, -2, -7, -8, UP, RIGHT_ARM);//THEIR RIGHT ARM
        add_plane(3, 4, 47, 16, 47, 32, -2, -7, -20, DOWN, RIGHT_ARM);

        add_plane(4, 12, 40, 20, 40, 36, -2, -7, -8, LEFT, RIGHT_ARM);
        add_plane(3, 12, 44, 20, 44, 36, 2, -7, -8, FRONT, RIGHT_ARM);
        add_plane(4, 12, 47, 20, 47, 36, -2, -4, -8, RIGHT, RIGHT_ARM);
        add_plane(3, 12, 51, 20, 51, 36, -2, -7, -8, BACK, RIGHT_ARM);
    } else {
        add_plane(4, 4, 36, 48, 52, 48, -2, 4, -8, UP, LEFT_ARM);//THEIR LEFT ARM
        add_plane(4, 4, 40, 48, 56, 48, -2, 4, -20, DOWN, LEFT_ARM);

        add_plane(4, 12, 32, 52, 48, 52, -2, 4, -8, LEFT, LEFT_ARM);
        add_plane(4, 12, 36, 52, 52, 52, 2, 4, -8, FRONT, LEFT_ARM);
        add_plane(4, 12, 40, 52, 56, 52, -2, 8, -8, RIGHT, LEFT_ARM);
        add_plane(4, 12, 44, 52, 60, 52, -2, 4, -8, BACK, LEFT_ARM);

        add_plane(4, 4, 44, 16, 44, 32, -2, -8, -8, UP, RIGHT_ARM);//THEIR RIGHT ARM
        add_plane(4, 4, 48, 16, 48, 32, -2, -8, -20, DOWN, RIGHT_ARM);

        add_plane(4, 12, 40, 20, 40, 36, -2, -8, -8, LEFT, RIGHT_ARM);
        add_plane(4, 12, 44, 20, 44, 36, 2, -8, -8, FRONT, RIGHT_ARM);
        add_plane(4, 12, 48, 20, 48, 36, -2, -4, -8, RIGHT, RIGHT_ARM);
        add_plane(4, 12, 52, 20, 52, 36, -2, -8, -8, BACK, RIGHT_ARM);
    }

    add_plane(4, 4, 20, 48, 4, 48, -2, 0, -20, UP, LEFT_LEG);//THEIR LEFT LEG
    add_plane(4, 4, 24, 48, 8, 48, -2, 0, -32, DOWN, LEFT_LEG);

    add_plane(4, 12, 16, 52, 0, 52, -2, 0, -20, LEFT, LEFT_LEG);
    add_plane(4, 12, 20, 52, 4, 52, 2, 0, -20, FRONT, LEFT_LEG);
    add_plane(4, 12, 24, 52, 8, 52, -2, 4, -20, RIGHT, LEFT_LEG);
    add_plane(4, 12, 28, 52, 12, 52, -2, 0, -20, BACK, LEFT_LEG);

    add_plane(4, 4, 4, 16, 4, 32, -2, -4, -20, UP, RIGHT_LEG);//THEIR RIGHT LEG
    add_plane(4, 4, 8, 16, 8, 32, -2, -4, -32, DOWN, RIGHT_LEG);

    add_plane(4, 12, 0, 20, 0, 36, -2, -4, -20, LEFT, RIGHT_LEG);
    add_plane(4, 12, 4, 20, 4, 36, 2, -4, -20, FRONT, RIGHT_LEG);
    add_plane(4, 12, 8, 20, 8, 36, -2, 0, -20, RIGHT, RIGHT_LEG);
    add_plane(4, 12, 12, 20, 12, 36, -2, -4, -20, BACK, RIGHT_LEG);

    // printf("%d\n", planes[0].size.x);
    for (int x = 0; x < SIZE; x++){
        for (int y = 0; y < SIZE; y++){
            color *c = &(pixels[y * SIZE + x]);
            c->r = 0;
            c->g = 0;
            c->b = 0;
            c->a = 0;
        }
    }
    for (int i = 0; i < planes.size(); i++){
        set_plane(planes[i]);
    }

    for (int x = 0; x < SIZE; x++){//just fixing what would minecraft fix anyways
        //should change it, so i can also fix transparency in inner layer
        for (int y = 0; y < SIZE; y++){
            color *c = &(pixels[y * SIZE + x]);
            if (c->a != 0) c->a = 255;
            else c->a = 0;
        }
    }
    write("out.png", pixels, SIZE, SIZE);
}