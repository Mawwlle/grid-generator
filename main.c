#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH 200
#define HEIGHT 200
#define POINTS WIDTH 
#define CHANNELS 3 

void draw_pixel(unsigned char* buffer, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int index = (y * WIDTH + x) * CHANNELS;
        buffer[index] = r;
        buffer[index + 1] = g;
        buffer[index + 2] = b;
    }
}

void draw_horizontal_line(unsigned char* buffer, int y, unsigned char r, unsigned char g, unsigned char b) {
    for (int x = 0; x < WIDTH; x++) {
        draw_pixel(buffer, x, y, r, g, b);
    }
}

void draw_vertical_line(unsigned char* buffer, int x, unsigned char r, unsigned char g, unsigned char b) {
    for (int y = 0; y < HEIGHT; y++) {
        draw_pixel(buffer, x, y, r, g, b);
    }
}

// y = f(x) в математических координатах (начало в центре, y вверх)
int wave(int x) {
    return 5 * sin(x / 2.0);
}

int parabola(int x) {
    return x * x / 4;
}

int linear(int x) {
    return x;
}

void make_grid(int grid[POINTS], int f(int x)) {
    for (int i = 0; i < POINTS; i++) {
        grid[i] = f(i - WIDTH / 2);
    }
}

void draw_grid(unsigned char* buffer, const int grid[POINTS], unsigned char r, unsigned char g, unsigned char b) {
    for (int i = 0; i < POINTS; i++) {
        int x = i;
        int y = HEIGHT / 2 - grid[i]; 
        draw_pixel(buffer, x, y, r, g, b);
    }
}
int main() {
    size_t buffer_size = WIDTH * HEIGHT * CHANNELS;
    unsigned char* buffer = (unsigned char*)malloc(buffer_size);
    
    if (!buffer) return 1;

    memset(buffer, 255, buffer_size);

    int center_x = WIDTH / 2;
    int center_y = HEIGHT / 2;
    int grid_step = 1; 
    int grid[POINTS];

    unsigned char axis_r = 0, axis_g = 0, axis_b = 0;

    draw_horizontal_line(buffer, center_y, axis_r, axis_g, axis_b);
    draw_vertical_line(buffer, center_x , axis_r, axis_g, axis_b);
    
    make_grid(grid, wave);
    draw_grid(buffer, grid, 255, 0, 0);

    make_grid(grid, linear);
    draw_grid(buffer, grid, 0, 255, 0);

    make_grid(grid, parabola);
    draw_grid(buffer, grid, 0, 0, 255);

    const char* filename = "coordinate_system.png";

    if (stbi_write_png(filename, WIDTH, HEIGHT, CHANNELS, buffer, WIDTH * CHANNELS)) {
    }

    free(buffer);
    return 0;
}

