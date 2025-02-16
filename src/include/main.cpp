#include <stdio.h>
#include <write.h>
#include <vector>

#include <call.h>

#define SIZE 64
color pixels[SIZE * SIZE];

struct plane {
    ivec2 size;
    ivec3 position;
    ivec2 inner_destination;
    ivec2 outer_destination;
    DIRECTION dir;
    PART part;
};

std::vector<plane> planes;

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

void set_plane(plane p){
    for (int x = 0; x < p.size.x; x++){
        for (int y = 0; y < p.size.y; y++){
            ivec2 inner_destination = {.x = x + p.inner_destination.x, .y = y + p.inner_destination.y};
            ivec2 outer_destination = {.x = x + p.outer_destination.x, .y = y + p.outer_destination.y};
            color inner = {.r = 0, .g = 0, .b = 0, .a = 255};
            color outer = {.r = 0, .g = 0, .b = 0, .a = 0};
            call(&inner, &outer, world_pos(p, x, y), ivec2{.x = x, .y = y}, p.size, p.dir, p.part);
            pixels[inner_destination.y * SIZE + inner_destination.x] = inner;
            pixels[outer_destination.y * SIZE + outer_destination.x] = outer;
        }
    }
}

int main( int argc, char *argv[] ){
    printf("hi\n");

    

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

    // for (int x = 0; x < SIZE; x++){//just fixing what would minecraft fix anyways
    //     //should change it, so i can also fix transparency in inner layer
    //     for (int y = 0; y < SIZE; y++){
    //         color *c = &(pixels[y * SIZE + x]);
    //         if (c->a != 0) c->a = 255;
    //         else c->a = 0;
    //     }
    // }
    write("out/out.png", pixels, SIZE, SIZE);
}