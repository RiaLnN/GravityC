#include "ui.h"

void change_color(struct pixel* pixels, int pos, uint8_t red, uint8_t green, uint8_t blue) {
    pixels[pos].red = red;
    pixels[pos].green = green;
    pixels[pos].blue = blue;
    pixels[pos].alpha = 1;
}

void draw_body(struct pixel* pixels, const OrbitalBody* body) {
    if (body == NULL) return;
    for (int y = body->y - body->radius; y < body->y + body->radius; y++) {
        if (y < 0 || y >= HEIGHT) continue;
        for (int x = body->x - body->radius; x < body->x + body->radius; x++) {
            if (x < 0 || x >= WIDTH) continue;
            long long dx = x - body->x;
            long long dy = y - body->y;
            long long d = dx * dx + dy * dy;
            if (d <= body->radius * body->radius) {
                change_color(pixels, y * WIDTH + x, body->color.red, body->color.green, body->color.blue);
            }
        }
    }
}
void draw_system(struct pixel* pixels, const System* sys) {
    for (int i = 0; i < sys->count; i++) {
        OrbitalBody* b = sys->bodies[i];
        draw_body(pixels, b);
    }
}
