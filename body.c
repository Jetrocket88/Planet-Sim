#include "body.h"
#include <stdio.h>

Body initialiseBody(CelestialType type, SDL_Color color, float mass, Vec2d pos,
                    Vec2d vel, Vec2d acc, double radius) {
    Body body;

    body.type = type;
    body.color = color;
    body.alive = true;

    body.mass = mass;     // kg
    body.radius = radius; // AU

    body.pos = pos; // AU
    body.vel = vel; // AU / second
    body.acc = acc; // AU / second * second
    body.trail = *initTrail();

    body.updateCount = 0;
    body.trailPollRate = 10;

    return body;
}

void updateBody(Body *bodies, size_t nBodies, size_t bodyIndex, double dt) {
    Body *cur = &bodies[bodyIndex];

    if (cur->updateCount++ > cur->trailPollRate) {
        //printf("Trail points being pushed for %zu\n", bodyIndex);
        trailPush(&cur->trail, cur->pos);
        cur->updateCount = 0;
    }

    cur->acc.x = 0.0f;
    cur->acc.y = 0.0f;

    for (size_t i = 0; i < nBodies; i++) {
        if (i == bodyIndex) {
            continue;
        }

        Body *other = &bodies[i];

        double dx = other->pos.x - cur->pos.x;
        double dy = other->pos.y - cur->pos.y;

        double distSq = dx * dx + dy * dy;
        double dist = sqrt(distSq);

        // a = G * m / r^3 * r_vector
        // this is the formula for n bodies
        double factor = G_AU * other->mass / (distSq * dist);
        printf("Factor between body %zu and body %zu: %e\n", bodyIndex, i, factor);

        // applies the acceleration due to gravity from other body
        // dx and dy are the components of the distance vector
        //  we multiply by factor to get the acceleration components
        cur->acc.x += factor * dx;
        cur->acc.y += factor * dy;
    }

    // applies the acceleration to velocity and position
    // dt is the timestep (very small value) to simulate the derivative
    cur->vel.x += cur->acc.x * dt;
    cur->vel.y += cur->acc.y * dt;

    cur->pos.x += cur->vel.x * dt;
    cur->pos.y += cur->vel.y * dt;
}

void updateAllBodies(Body *bodies, size_t nBodies, float dt) {
    for (size_t i = 0; i < nBodies; i++) {
        updateBody(bodies, nBodies, i, dt);
    }
    return;
}

bool checkCollision(Body b1, Body b2) {
    double dx = b2.pos.x - b1.pos.x;
    double dy = b2.pos.y - b1.pos.y;
    double distanceSquared = dx * dx + dy * dy;
    double radiiSum = b1.radius + b2.radius;
    double radiiSumSq = radiiSum * radiiSum;
    return distanceSquared <= radiiSumSq;
}

void handleCollisions(Body *bodies, size_t nBodies) {
    for (size_t i = 0; i < nBodies; i++) {
        Body *cur = &bodies[i];
        for (size_t j = 0; j < nBodies; j++) {
            Body *other = &bodies[j];
            if (j == i)
                continue;
            if (checkCollision(*cur, bodies[j]) && cur->alive &&
                bodies[j].alive) {
                if (cur->mass >= other->mass) {
                    cur->mass += other->mass * 0.2;
                    cur->radius *= 1.1;
                    other->alive = false;
                } else {
                    other->mass += cur->mass * 0.2;
                    other->radius *= 1.1;
                    cur->alive = false;
                }
            }
        }
    }
    return;
}

void freeBody(Body *body) { free(body); };

void drawTrail(SDL_Renderer *prenderer, Camera* cam, Body *body) {
    size_t start = (body->trail.trailHead + MAX_TRAIL_LENGTH - body->trail.trailCount) % MAX_TRAIL_LENGTH;
    for (size_t i = 1; i < body->trail.trailCount; i++) {
        size_t i0 = (start + i - 1) % MAX_TRAIL_LENGTH; // previous point
        size_t i1 = (start + i) % MAX_TRAIL_LENGTH;     // current point
        Vec2d startPos = worldToScreen(body->trail.points[i0], cam);
        Vec2d endPos = worldToScreen(body->trail.points[i1], cam);
        SDL_Color trailColor = {body->color.r, body->color.g, body->color.b, body->color.a / 8};
        drawLine(prenderer, trailColor, startPos, endPos);
    }
}
