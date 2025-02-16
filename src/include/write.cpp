#include <write.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

void write(const char *name, color *pixels, int w, int h){
    printf("writing png\n");
    int comp = 4;
    int pngret = stbi_write_png(name, w, h, comp, (void *)pixels, w * comp);
    if (pngret == 0) {
        printf("failed to write png\n");
        return;
    }
    printf("success\n");
}