#ifndef BODY_H
#define BODY_H

#include "helpers.h"
#include "units.h"
#include "trail.h"
#include "Camera.h"

#include "SDL3/SDL_pixels.h"

#include <stdio.h>

typedef enum { STAR, PLANET, MOON } CelestialType;

typedef struct {
    CelestialType type;
    SDL_Color color;
    float mass;

    Vec2d pos;
    Vec2d vel;
    Vec2d acc;

    Trail trail;

    double radius;
    bool alive;

    size_t updateCount;
    size_t trailPollRate;
} Body;


Body initialiseBody(CelestialType type, SDL_Color color, float mass, Vec2d pos, Vec2d vel, Vec2d acc, double radius);
void updateBody(Body* bodies, size_t nBodies, size_t bodyIndex, double dt); 
void updateAllBodies(Body* bodies, size_t nBodies, float dt);
void handleCollisions(Body *bodies, size_t nBodies);
void drawTrail(SDL_Renderer *prenderer, Camera* cam,  Body *body);

#endif //BODY_H
