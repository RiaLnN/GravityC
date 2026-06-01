#include "logic.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

void apply_gravity(OrbitalBody* a, OrbitalBody* b) {
    if (a == NULL || b == NULL) return;
    double dx = b->x - a->x;
    double dy = b->y - a->y;
    double dist_sq = dx*dx + dy*dy + 1.0;
    double dist = sqrt(dist_sq);

    double force = (G_CONST * a->mass * b->mass) / dist_sq;

    double acceleration = force / a->mass;
    if (acceleration > 100.0) acceleration = 100.0;
    a->vx += (acceleration * dx / dist);
    a->vy += (acceleration * dy / dist);
}

void set_circular_orbit(OrbitalBody* body, OrbitalBody* center) {
    double dx = body->x - center->x;
    double dy = body->y - center->y;
    double R = sqrt(dx * dx + dy * dy);

    double v_mag = sqrt((G_CONST * center->mass) / R);

    body->vx = (-dy / R) * v_mag;
    body->vy = (dx / R) * v_mag;
}
void reset_body(System* sys, int pos) {
    free(sys->bodies[pos]);
    for (int j = pos; j < sys->count - 1; j++) {
        sys->bodies[j] = sys->bodies[j + 1];
    }
    sys->count--;
}
void obstacle_check(System* sys) {
    for (int i = 0; i < sys->count; i++) {
        for (int j = i + 1; j < sys->count; j++) {
            OrbitalBody* b1 = sys->bodies[i];
            OrbitalBody* b2 = sys->bodies[j];

            double dx = b2->x - b1->x;
            double dy = b2->y - b1->y;
            double dist_sq = dx * dx + dy * dy;
            double radius_sum = b1->radius + b2->radius;

            if (dist_sq <= radius_sum * radius_sum) {
                double total_mass = b1->mass + b2->mass;

                double new_vx = (b1->vx * b1->mass + b2->vx * b2->mass) / total_mass;
                double new_vy = (b1->vy * b1->mass + b2->vy * b2->mass) / total_mass;

                if (b1->mass >= b2->mass) {
                    b1->vx = new_vx;
                    b1->vy = new_vy;
                    b1->mass = total_mass;
                    b1->radius = sqrt(b1->radius * b1->radius + b2->radius * b2->radius);

                    reset_body(sys, j);
                    j--;
                } else {
                    b2->vx = new_vx;
                    b2->vy = new_vy;
                    b2->mass = total_mass;
                    b2->radius = sqrt(b1->radius * b1->radius + b2->radius * b2->radius);

                    reset_body(sys, i);
                    i--;
                    break;
                }
            }
        }
    }
}
void edge_check(System* sys) {
    for (int i = 0; i < sys->count; i++) {
        if (sys->bodies[i]->x > WIDTH) sys->bodies[i]->x = 10;
        else if (sys->bodies[i]->x < 0) sys->bodies[i]->x = WIDTH - 10;
        if (sys->bodies[i]->y > HEIGHT) sys->bodies[i]->y = 10;
        else if (sys->bodies[i]->y < 0) sys->bodies[i]->y = HEIGHT - 10;
    }
}
void update_system(System* sys) {
    for (int i = 0; i < sys->count; i++) {
        for (int j = 0; j < sys->count; j++) {
            if (i == j) continue;
            apply_gravity(sys->bodies[i], sys->bodies[j]);
        }
    }
    for (int i = 0; i < sys->count; i++) {
        if (sys->bodies[i] == NULL) continue;
        sys->bodies[i]->x += sys->bodies[i]->vx;
        sys->bodies[i]->y += sys->bodies[i]->vy;
        printf("x:%f y:%f\n", sys->bodies[i]->x, sys->bodies[i]->y);
    }
    if (OBSTACLE_ENABLE) obstacle_check(sys);
    if (EDGE_ENABLE) edge_check(sys);
}

OrbitalBody* create_body(float mass, float radius, struct pixel color, double x, double y) {
    OrbitalBody* body = malloc(sizeof(OrbitalBody));
    body->radius = radius;
    if (body->radius < 1) body->radius = 1;
    body->mass = mass;
    body->color = color;
    body->vx = 0;
    body->vy = 0;

    body->x = x;
    body->y = y;

    return body;
}
