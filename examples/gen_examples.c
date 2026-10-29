// Генератор картинок-примеров: переиспользует функции из main.c
#define main original_main
#include "../main.c"
#undef main

#include <stdio.h>

int cubic(int x) {
    return x * x * x / 400;
}

int absolute(int x) {
    return abs(x) - 50;
}

int big_wave(int x) {
    return 40 * sin(x / 15.0);
}

typedef struct {
    const char* filename;
    int (*f)(int x);
    unsigned char r, g, b;
} Example;

void render(const char* filename, const Example* curves, int count) {
    size_t buffer_size = WIDTH * HEIGHT * CHANNELS;
    unsigned char* buffer = malloc(buffer_size);
    int grid[POINTS];

    if (!buffer) return;
    memset(buffer, 255, buffer_size);

    draw_horizontal_line(buffer, HEIGHT / 2, 0, 0, 0);
    draw_vertical_line(buffer, WIDTH / 2, 0, 0, 0);

    for (int i = 0; i < count; i++) {
        make_grid(grid, curves[i].f);
        draw_grid(buffer, grid, curves[i].r, curves[i].g, curves[i].b);
    }

    stbi_write_png(filename, WIDTH, HEIGHT, CHANNELS, buffer, WIDTH * CHANNELS);
    printf("%s\n", filename);
    free(buffer);
}

int main() {
    Example examples[] = {
        {"wave.png",     wave,     255, 0,   0},
        {"linear.png",   linear,   0,   200, 0},
        {"parabola.png", parabola, 0,   0,   255},
        {"cubic.png",    cubic,    200, 0,   200},
        {"absolute.png", absolute, 255, 140, 0},
        {"big_wave.png", big_wave, 0,   150, 150},
    };
    int count = sizeof(examples) / sizeof(examples[0]);

    for (int i = 0; i < count; i++) {
        render(examples[i].filename, &examples[i], 1);
    }
    render("all.png", examples + 3, 3);
    return 0;
}
