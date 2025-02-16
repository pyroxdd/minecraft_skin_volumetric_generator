#pragma once

struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

void write(const char *name, color *pixels, int w, int h);