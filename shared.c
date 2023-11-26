#include "shared.h"
#include <stdio.h>
#include <stdlib.h>

#include <glib.h>

#include <ymir/graphics.h>

ScreenSize get_screen_size(int argc, char *argv[]) {
    ScreenSize screen_size = { .width = WIDTH, .height = HEIGHT};
    GError* error = NULL;
    GOptionContext* context;

    GOptionEntry entries[] = {
        { "width", 'w', 0, G_OPTION_ARG_INT, &(screen_size.width), "Width of the area", "WIDTH" },
        { "height", 'h', 0, G_OPTION_ARG_INT, &(screen_size.height), "Height of the area", "DEPTH" },
        { NULL }
    };

    context = g_option_context_new("Basic Mandelbrot");
    g_option_context_add_main_entries(context, entries, NULL);

    if (!g_option_context_parse(context, &argc, &argv, &error)) {
        g_print("option parsing failed: %s\n", error->message);
        exit(1);
    }

    g_option_context_free(context);

    return screen_size;
}


void write_mandel_image(const char* fname, ScreenSize screen_size, uint8_t* mandel_area) {
    pixel_t** image = alloc_image(screen_size.height, screen_size.width);
    for (int y = 0; y < screen_size.height; y++) {
        for (int x = 0; x < screen_size.width; x++) {
            image[y][x] = (pixel_t) { .r = mandel_area[y * screen_size.width + x], .g = 0, .b = 0 };
        }
    }
    write_png(fname, image, screen_size.height, screen_size.width);
    free_image(image, screen_size.height);
}

