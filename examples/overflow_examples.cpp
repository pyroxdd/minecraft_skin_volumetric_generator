void a(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static FastNoiseLite noise = []() {
        FastNoiseLite n;
        n.SetSeed(73458);
        n.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        n.SetFrequency(0.07f);
        return n;
    }();
    double off_scale = 2;
    double n = noise.GetNoise(float(world_pos.x * off_scale + 978913), float(world_pos.y * off_scale + 127630), float(world_pos.z * off_scale + 19972));
    n = (n + 1) / 2 * 10 + 9;
    double v = abs(world_pos.x + world_pos.y * 2 + world_pos.z + n);
    unsigned char o = v * 9.8;
    *inner = color{.r = o, .g = o, .b = o, .a = 255};
}

void b(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static FastNoiseLite noise = []() {
        FastNoiseLite n;
        n.SetSeed(487946);
        n.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        n.SetFrequency(0.07f);
        return n;
    }();
    double off_scale = 2;
    double n = noise.GetNoise(float(world_pos.x * off_scale + 978913), float(world_pos.y * off_scale + 127630), float(world_pos.z * off_scale + 19972));
    n = (n + 1) / 2 * 10 + 19;
    double v = (world_pos.x - world_pos.y + world_pos.z * 2 + n) * 5.2;
    if (v < 0) {
        v *= -1;
        unsigned char s = v / 26;
        switch (s){
            case 0:
                *inner = color{.r = 0, .g = 0, .b = 0, .a = 255};
                break;
            case 1:
                *inner = color{.r = 5, .g = 0, .b = 30, .a = 255};
                break;
            case 2:
                *inner = color{.r = 12, .g = 0, .b = 50, .a = 255};
                break;
            case 3:
                *inner = color{.r = 22, .g = 0, .b = 65, .a = 255};
                break;
            case 4:
                *inner = color{.r = 37, .g = 0, .b = 72, .a = 255};
                break;
            case 5:
                *inner = color{.r = 60, .g = 0, .b = 75, .a = 255};
                break;
            case 6:
                *inner = color{.r = 90, .g = 7, .b = 70, .a = 255};
                break;
            case 7:
                *inner = color{.r = 110, .g = 23, .b = 58, .a = 255};
                break;
            case 8:
                *inner = color{.r = 120, .g = 49, .b = 33, .a = 255};
                break;
            case 9:
                *inner = color{.r = 125, .g = 86, .b = 7, .a = 255};
                break;
        }
        if (s % 2) *outer = *inner;
        // *inner = color{.r = (unsigned char)(v), .g = (unsigned char)(v * 0.7), .b = (unsigned char)(v), .a = 255};
    }
    else {
        unsigned char s = v / 21;
        switch (s){
            case 0:
                *inner = color{.r = 0, .g = 5, .b = 0, .a = 255};
                break;
            case 1:
                *inner = color{.r = 0, .g = 12, .b = 5, .a = 255};
                break;
            case 2:
                *inner = color{.r = 0, .g = 21, .b = 15, .a = 255};
                break;
            case 3:
                *inner = color{.r = 0, .g = 35, .b = 25, .a = 255};
                break;
            case 4:
                *inner = color{.r = 0, .g = 53, .b = 35, .a = 255};
                break;
            case 5:
                *inner = color{.r = 10, .g = 73, .b = 60, .a = 255};
                break;
            case 6:
                *inner = color{.r = 30, .g = 92, .b = 85, .a = 255};
                break;
            case 7:
                *inner = color{.r = 60, .g = 107, .b = 110, .a = 255};
                break;
            case 8:
                *inner = color{.r = 100, .g = 113, .b = 140, .a = 255};
                break;
            // case 9:
            //     *inner = color{.r = 150, .g = 115, .b = 170, .a = 255};
            //     break;
        }
        if (!(s % 2)) *outer = *inner;
        //*inner = color{.r = (unsigned char)(v), .g = (unsigned char)(v), .b = (unsigned char)(v), .a = 255};
    }
}

void c(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static FastNoiseLite noise = []() {
        FastNoiseLite n;
        n.SetSeed(77779);
        n.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        n.SetFrequency(0.07f);
        return n;
    }();
    double off_scale = 2;
    double n = noise.GetNoise(float(world_pos.x * off_scale + 978913), float(world_pos.y * off_scale + 127630), float(world_pos.z * off_scale + 19972));
    n = (n + 1) / 2 * 7 + 14;
    double v = (world_pos.x - world_pos.y * 2.5 + world_pos.z + n) * 5.2;
    bool positive = true;
    if (v < 0){
        v *= -1;
        positive = false;
    }
    double dist = distance(world_pos.x, world_pos.y, world_pos.z, 0, 0, -13);
    double dval = 8 - dist;
    if (dval < 0) dval = 0;
    v -= dval * 9 + 6 + 8;
    double ov = v + 5;

    double sn = (noise.GetNoise(float(world_pos.x * off_scale + 75351), float(world_pos.y * off_scale + 94537), float(world_pos.z * off_scale + 34567)) + 1) / 2;
    if (v < 0){
        //generate inner clr
        v *= 4;
        v = int(v / 50) * 50 - 1;
        *inner = color{.r = (unsigned char)(85 + (v / 3)), .g = (unsigned char)(255 - v), .b = (unsigned char)(v), .a = 255};
        // *inner = color{.r = 255, .g = 0, .b = 0, .a = 255};
    } else{
        //generate inner rock
        double rsn = int(sn * 255 / 51) * 15 + 20;
        *inner = color{.r = (unsigned char)(rsn), .g = (unsigned char)(rsn * 0.85), .b = (unsigned char)(rsn * 0.7), .a = 255};
    }
    if (ov > 0){
        //generate outer shell
        off_scale = 3;
        
        if (ov < 40 || sn > 0.6) {
            double rsn = int(sn * 255 / 51) * 20 + 40;
            *outer = color{.r = (unsigned char)(rsn), .g = (unsigned char)(rsn * 0.85), .b = (unsigned char)(rsn * 0.7), .a = 255};
        }
    }
    // double vdec = 5;
    // bool gen_in = false;
    // if (v < 0) {
    //     gen_in = true;
    // }
    // else {
    //     off_scale = 3;
    //     double sn = noise.GetNoise(float(world_pos.x * off_scale + 75351), float(world_pos.y * off_scale + 984102), float(world_pos.z * off_scale + 34567));
    //     double thisv = v + sn * 20;
    //     color out = color{.r = (unsigned char)(thisv), .g = (unsigned char)(thisv), .b = (unsigned char)(thisv), .a = 255};
    //     thisv -= 4;
    //     if (thisv < 0){
    //         gen_in = true;
    //     } else *inner = color{.r = (unsigned char)(thisv), .g = (unsigned char)(thisv), .b = (unsigned char)(thisv), .a = 255};
    //     *outer = out;
    // }
    // if (gen_in){
    //     v -= 5;
    //     v *= 4;
    //     v = int(v / 50) * 50 - 1;
    //     *inner = color{.r = (unsigned char)(85 + (v / 3)), .g = (unsigned char)(255 - v), .b = (unsigned char)(v), .a = 255};
    // }
}

void d(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    double v = double(world_pos.x + world_pos.y + world_pos.z - 7) / 22;
    *inner = spectrum(v);
}

void e(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    double v = direction_difference(6, 6, -4, -1, -1, -2, world_pos.x, world_pos.y, world_pos.z) / 4;
    double l = 12;
    v = int(v * l) / l;
    *inner = spectrum(v);
}

void f(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    if (is_exposed(dir, part, plane_pos)) *inner = c(255, 255, 255, 255);
    else *inner = c(0, 0, 0, 255);
}

void g(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    switch (dir){
        case LEFT:
            *inner = c(155, 155, 155, 255);
            break;
        case RIGHT:
            *inner = c(105, 105, 105, 255);
            break;
        case UP:
            *inner = c(255, 255, 255, 255);
            break;
        case DOWN:
            *inner = c(0, 0, 0, 255);
            break;
        case FRONT:
            *inner = c(205, 205, 205, 255);
            break;
        case BACK:
            *inner = c(55, 55, 55, 255);
            break;
    }
}

void h(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    int b = 255;
    switch (dir){
        case LEFT:
            b -= 102;
            break;
        case RIGHT:
            b -= 153;
            break;
        case UP:
            // -= 0
            break;
        case DOWN:
            b -= 255;
            break;
        case FRONT:
            b -= 51;
            break;
        case BACK:
            b -= 204;
            break;
    }

    if (!is_exposed(dir, part, plane_pos)) b -= 51;
    if (b < 0) b = 0;

    *inner = c(b, b, b, 255);
}

void i(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static bool initialized = []() {
        srand(9489456);
        return true;
    }();
    int b = rand() % 255;
    *inner = c(b, b, b, 255);
}

void j(color *inner, color *outer, ivec3 world_pos, ivec2 plane_pos, ivec2 plane_size, DIRECTION dir, PART part){
    static FastNoiseLite noise = []() {
        FastNoiseLite n;
        n.SetSeed(978651);
        n.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        n.SetFrequency(0.12f);
        return n;
    }();
    double mult = 3.5;
    double on = (noise.GetNoise(float(world_pos.x * 3 + 19794.736), float(world_pos.y * 3 + 873495.764), float(world_pos.z * 0.7 + 673490.437)) + 1);

    double n1 = (noise.GetNoise(float(world_pos.x), float(world_pos.y)) + 1) * mult + 1;
    double n2 = (noise.GetNoise(float(world_pos.x + 519984.974), float(world_pos.y + 591948.346)) + 1) * mult + 1;
    double n3 = (noise.GetNoise(float(world_pos.x + 984805.615), float(world_pos.y + 61723.178)) + 1) * mult + 1;
    double n4 = (noise.GetNoise(float(world_pos.x + 35864.918), float(world_pos.y + 780642.645)) + 1) * mult + 1;
    double n5 = (noise.GetNoise(float(world_pos.x + 203875.127), float(world_pos.y + 45769.401)) + 1) * mult + 1;
    double n6 = (noise.GetNoise(float(world_pos.x + 796453.764), float(world_pos.y + 197536.828)) + 1) * mult + 1;
    double n7 = (noise.GetNoise(float(world_pos.x + 536571.644), float(world_pos.y + 37061.826)) + 1) * mult + 1;
    double n8 = (noise.GetNoise(float(world_pos.x + 457861.976), float(world_pos.y + 276849.046)) + 1) * mult + 1;
    if (32 + world_pos.z > n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8) *inner = c(10, 0, 55, 255);
    else if (32 + world_pos.z > n1 + n2 + n3 + n4 + n5 + n6 + n7) *inner = c(30, 0, 42, 255);
    else if (32 + world_pos.z > n1 + n2 + n3 + n4 + n5 + n6) *inner = c(100, 0, 30, 255);
    else if (32 + world_pos.z > n1 + n2 + n3 + n4 + n5) *inner = c(180, 0, 20, 255);
    else if (32 + world_pos.z > n1 + n2 + n3 + n4) *inner = c(255, 30, 10, 255);
    else if (32 + world_pos.z > n1 + n2 + n3) *inner = c(255, 100, 0, 255);
    else if (32 + world_pos.z > n1 + n2) *inner = c(255, 180, 0, 255);
    else if (32 + world_pos.z > n1) *inner = c(255, 255, 0, 255);
    else *inner = c(255, 255, 255, 255);

    if (on < 0.7) {
        double omult = 1.3;
        if (inner->r * omult > 255) outer->r = 255;
        else outer->r = inner->r * omult;
        if (inner->g * omult > 255) outer->g = 255;
        else outer->g = inner->g * omult;
        if (inner->b * omult > 255) outer->b = 255;
        else outer->b = inner->b * omult;
        outer->a = 255;
    }
}