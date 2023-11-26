#ifndef _SHARED_H_
#define _SHARED_H_

#include <stdint.h>

#define WIDTH 2048
#define HEIGHT 1024

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ScreenSize {
    int width;
    int height;
} ScreenSize;

ScreenSize get_screen_size(int argc, char *argv[]);
void write_mandel_image(const char* fname, ScreenSize screen_size, uint8_t* mandel_area);

#ifdef __cplusplus
}
#endif

#endif
