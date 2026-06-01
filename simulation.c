#include <stdlib.h>
#include "simulation.h"
#include <math.h>

System* create_random_system(int sys_size) {
    System* sys = malloc(sizeof(System));
    sys->count = sys_size;
    sys->bodies = malloc(sizeof(OrbitalBody*) * sys_size);
    struct pixel color;
    color.red = 100; color.green = 100; color.blue = 100; color.alpha = 1;
    for (int i = 0; i < sys_size; i++) {
        OrbitalBody* b = create_body(1000000000, 10, color, (rand() % (WIDTH - 200)) + 100, (rand() % (HEIGHT - 200)) + 100);
        sys->bodies[i] = b;
    }
    return sys;
}

System* create_solar_system() {
    System* sys = malloc(sizeof(System));
    sys->count = 9;
    sys->bodies = malloc(sizeof(OrbitalBody*) * 9);
    struct pixel sun_color;
    sun_color.red = 255; sun_color.green = 255; sun_color.blue = 0; sun_color.alpha = 1;

    struct pixel mercury_color;
    mercury_color.red = 100; mercury_color.green = 100; mercury_color.blue = 100; mercury_color.alpha = 1;

    struct pixel venus_color;
    venus_color.red = 255; venus_color.green = 165; venus_color.blue = 0; venus_color.alpha = 1;

    struct pixel earth_color;
    earth_color.red = 0; earth_color.green = 255; earth_color.blue = 100; earth_color.alpha = 1;

    struct pixel mars_color;
    mars_color.red = 255; mars_color.green = 10; mars_color.blue = 0; mars_color.alpha = 1;

    struct pixel jupiter_color;
    jupiter_color.red = 150; jupiter_color.green = 75; jupiter_color.blue = 0; jupiter_color.alpha = 1;

    struct pixel saturn_color;
    saturn_color.red = 150; saturn_color.green = 55; saturn_color.blue = 0; saturn_color.alpha = 1;

    struct pixel uran_color;
    uran_color.red = 0; uran_color.green = 55; uran_color.blue = 255; uran_color.alpha = 1;

    struct pixel neptune_color;
    neptune_color.red = 0; neptune_color.green = 10; neptune_color.blue = 255; neptune_color.alpha = 1;
    int center_x = WIDTH / 2; int center_y = HEIGHT / 2;
    OrbitalBody* sun = create_body(10000000000000, 40, sun_color, center_x, center_y);
    OrbitalBody* mercury = create_body(1000000, 10, mercury_color, center_x + 80, center_y);
    OrbitalBody* venus = create_body(100000000, 20, venus_color, center_x, center_y + 120);
    OrbitalBody* earth = create_body(1000000000, 20, earth_color, center_x + 180, center_y);
    OrbitalBody* mars = create_body(1000000000, 20, mars_color, center_x, center_y + 220);
    OrbitalBody* jupiter = create_body(10000000000, 30, jupiter_color, center_x + 290, center_y);
    OrbitalBody* saturn = create_body(7000000000, 28, saturn_color, center_x, center_y + 380);
    OrbitalBody* uran = create_body(100000000, 21, uran_color, center_x + 440, center_y);
    OrbitalBody* neptune = create_body(100000000, 22, neptune_color, center_x, center_y+520);

    sys->bodies[0]=sun; sys->bodies[1]=mercury; sys->bodies[2]=venus; sys->bodies[3]=earth; sys->bodies[4]=mars; sys->bodies[5]=jupiter;
    sys->bodies[6]=saturn; sys->bodies[7]=uran; sys->bodies[8]=neptune;

    set_circular_orbit(mercury, sun);
    set_circular_orbit(venus, sun);
    set_circular_orbit(earth, sun);
    set_circular_orbit(mars, sun);
    set_circular_orbit(jupiter, sun);
    set_circular_orbit(saturn, sun);
    set_circular_orbit(uran, sun);
    set_circular_orbit(neptune, sun);

    return sys;
}

System* create_saturn(int satelite_count) {
    System* sys = malloc(sizeof(System));
    sys->count = satelite_count + 1;
    sys->bodies = malloc(sizeof(OrbitalBody*) * (satelite_count + 2));
    struct pixel satelite_color;
    satelite_color.red = 100; satelite_color.green = 100; satelite_color.blue = 100; satelite_color.alpha = 1;
    struct pixel saturn_color;
    saturn_color.red = 150; saturn_color.green = 55; saturn_color.blue = 0; saturn_color.alpha = 1;
    int center_x = WIDTH / 2; int center_y = HEIGHT / 2;
    OrbitalBody* saturn = create_body(10000000000000, 40, saturn_color, center_x, center_y);
    sys->bodies[0] = saturn;
    for (int i = 1; i < sys->count; i++) {
        double angle = ((double)rand() / RAND_MAX) * 2.0 * PI;

        double min_dist = saturn->radius * 2.5;
        double max_dist = min_dist + 200.0;
        double r = min_dist + ((double)rand() / RAND_MAX) * (max_dist - min_dist);

        double rand_x = saturn->x + r * cos(angle);
        double rand_y = saturn->y + r * sin(angle);

        OrbitalBody* b = create_body(10000, 1, satelite_color, rand_x, rand_y);

        set_circular_orbit(b, saturn);

        sys->bodies[i] = b;
    }
    return sys;
}