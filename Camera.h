#ifndef CAMERA_H
#define CAMERA_H

#include "helpers.h"
#include "SDL3/SDL_keyboard.h"
#include "body.h"

typedef struct {
    Vec2d pos;
    double zoom;
    int width, height, speed;
} Camera;


Camera initialiseCamera(Vec2d pos, float speed, int width, int height, double zoom);
Vec2d worldToScreen(Vec2d world, Camera* cam);
void moveCamera(Camera* cam, float dt);


#endif // CAMERA_H
