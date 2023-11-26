#include "shared.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER 1000


int compute_mandelbrot_point(double cx, double cy) {
    double zx, zy, zx2, zy2;
    zx = 0.0;
    zy = 0.0;
    zx2 = zx * zx;
    zy2 = zy * zy;
    int iter = 0;
    while (iter < MAX_ITER && zx2 + zy2 < 4.0) {
        zy = 2.0 * zx * zy + cy;
        zx = zx2 - zy2 + cx;
        zx2 = zx * zx;
        zy2 = zy * zy;
        iter++;
    }
    return iter;
}


uint8_t* compute_all_mandelbrot(int width, int height) {
    uint8_t* area = malloc(sizeof(uint8_t) * width * height);
    int x, y;
    double cx, cy;
    for (y = 0; y < height; y++) {
        cy = ((double)y / height) * 4.0 - 2.0;
        for (x = 0; x < width; x++) {
            cx = ((double)x / width) * 4.0 - 2.0;
            int iter;
            iter = compute_mandelbrot_point(cx, cy);
            area[y * width + x] = iter;
        }
    }
    return area;
}


int main(int argc, char *argv[]) {
    uint8_t* mandel_area;
    ScreenSize screen_size = get_screen_size(argc, argv);

    printf("Width: %d, Height: %d\n", screen_size.width, screen_size.height);
    mandel_area = compute_all_mandelbrot(screen_size.width, screen_size.height);

    write_mandel_image("basic.png", screen_size, mandel_area);

    free(mandel_area);

    return 0;
}
