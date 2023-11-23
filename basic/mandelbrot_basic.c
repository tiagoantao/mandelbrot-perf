#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


void draw_mandelbrot(int *area, int width, int height) {
    int x, y;
    int max_iter = 1000;
    double cx, cy;
    double zx, zy, zx2, zy2;
    for (y = 0; y < height; y++) {
        cy = ((double)y / height) * 4.0 - 2.0;
        for (x = 0; x < width; x++) {
            cx = ((double)x / width) * 4.0 - 2.0;
            zx = 0.0;
            zy = 0.0;
            zx2 = zx * zx;
            zy2 = zy * zy;
            int iter = 0;
            while (iter < max_iter && zx2 + zy2 < 4.0) {
                zy = 2.0 * zx * zy + cy;
                zx = zx2 - zy2 + cx;
                zx2 = zx * zx;
                zy2 = zy * zy;
                iter++;
            }
            area[y * width + x] = iter;
        }
    }
}


int main(int argc, char *argv[]) {
    GError *error = NULL;
    GOptionContext *context;

    int width = 640;
    int height = 480;

    GOptionEntry entries[] = {
        { "width", 'w', 0, G_OPTION_ARG_INT, &width, "Width of the area", "WIDTH" },
        { "height", 'h', 0, G_OPTION_ARG_INT, &height, "Height of the area", "DEPTH" },
        { NULL }
    };

    context = g_option_context_new("Basic Mandelbrot");
    g_option_context_add_main_entries(context, entries, NULL);

    if (!g_option_context_parse(context, &argc, &argv, &error)) {
        g_print("option parsing failed: %s\n", error->message);
        exit(1);
    }

    g_option_context_free(context);

    printf("Width: %d, Height: %d\n", width, height);
    mandel_area = malloc(sizeof(int) * width * height);
    draw_mandelbrot(mandel_area, width, height);

    return 0;
}
