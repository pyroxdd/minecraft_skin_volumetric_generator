#include <call.h>

bool slim = true;

void call(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static FastNoiseLite noise = []() {
        FastNoiseLite n;
        n.SetSeed(73458);
        n.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        n.SetFrequency(0.07f);
        return n;
    }();
    double off_scale = 1;
    double off_x = noise.GetNoise(float(world_pos.x * off_scale + 19972), float(world_pos.y * off_scale + 978913), float(world_pos.z * off_scale + 127630));

    double off_y = noise.GetNoise(float(world_pos.x * off_scale + 786412), float(world_pos.y * off_scale + 45738), float(world_pos.z * off_scale + 768431));

    double off_z = noise.GetNoise(float(world_pos.x * off_scale + 334761), float(world_pos.y * off_scale + 897566), float(world_pos.z * off_scale + 561974));
    double off_mult = 8.3;
    double dv = (noise.GetNoise(float(world_pos.x) + off_x * off_mult, float(world_pos.y) + off_y * off_mult, float(world_pos.z) + off_z * off_mult) + 1) / 2;

    *inner = color{.r = 255, .g = (unsigned char)((1 - dv) * 255), .b = (unsigned char)(dv * 255), .a = 255};

    if (dv < 0.4) *outer = *inner;
}