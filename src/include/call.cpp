#include <call.h>

bool slim = true;

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static FastNoiseLite noise = []() {
        FastNoiseLite n;
        n.SetSeed(346791);
        n.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        n.SetFrequency(0.12f);
        return n;
    }();
    double n1 = (noise.GetNoise(float(world_pos.x), float(world_pos.y)) + 1) / 2;
    double n2 = (noise.GetNoise(float(world_pos.x + 41947.347), float(world_pos.y + 39746.213)) + 1) / 2;
    int inc = 11;
    n1 = n1 * 5 + 2;
    n2 = n2 * 5 + 2;
    if (32 + world_pos.z > n1 + n2 + inc) {
        // *inner = c(255, 255, 0, 255);
    }
    else if (32 + world_pos.z > n1 + inc) {
        *inner = c(255, 0, 127, 255);
    }
}