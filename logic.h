#ifndef LOGIC_H
#define LOGIC_H
#include <stdint.h>

#define HEIGHT 1200
#define WIDTH 1600
#define PI 3.14
#define G_CONST 0.0000000001
#define EDGE_ENABLE true
#define OBSTACLE_ENABLE true
struct pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
} __attribute__((__packed__));

typedef struct OrbitalBody {
    float radius;
    struct pixel color;
    double x, y;
    double vx, vy;
    double  mass;

} OrbitalBody;

typedef struct {
    OrbitalBody** bodies;
    int count;
} System;



OrbitalBody* create_body(float mass, float radius, struct pixel color, double x, double y);
void update_system(System* sys);
void set_circular_orbit(OrbitalBody* body, OrbitalBody* center);
#endif