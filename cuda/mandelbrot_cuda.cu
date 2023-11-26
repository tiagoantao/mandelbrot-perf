#include "shared.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER 1000


__global__
void compute_mandelbrot_vertical(int width, int height, uint8_t* area) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    double cx = ((double)x / width) * 4.0 - 2.0;
    for (int y=0; y<height; y++)  {
        double cy = ((double)y / height) * 4.0 - 2.0;
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
        area[y * width + x] = iter;
    }
}


uint8_t* compute_all_mandelbrot(int width, int height) {
    uint8_t* garea;
    uint8_t* area;
    int size = width * height * sizeof(uint8_t);
    area = (uint8_t*)malloc(size);
    cudaMallocManaged(&garea, size);
    compute_mandelbrot_vertical<<<width/256, 256>>>(width, height, garea);
    cudaDeviceSynchronize();
    cudaMemcpy(area, garea, size, cudaMemcpyDeviceToHost);
    cudaFree(garea);
    return area;
}


int main(int argc, char *argv[]) {
    uint8_t* mandel_area;
    ScreenSize screen_size = get_screen_size(argc, argv);

    printf("Width: %d, Height: %d\n", screen_size.width, screen_size.height);
    mandel_area = compute_all_mandelbrot(screen_size.width, screen_size.height);

    write_mandel_image("cuda.png", screen_size, mandel_area);

    free(mandel_area);

    return 0;
}
