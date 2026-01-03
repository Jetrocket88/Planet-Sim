#include "Camera.h"

Camera initialiseCamera(Vec2d pos, float speed, int width, int height, double zoom) {
    Camera c;
    c.pos    = pos;
    c.speed  = speed;
    c.width  = width;
    c.height = height;
    c.zoom   = zoom;
    return c;
}


Vec2d worldToScreen(Vec2d world, Camera* cam) {
    Vec2d screen;
    screen.x = (world.x - cam->pos.x) * cam->zoom + ((float)cam->width / 2);
    screen.y = (world.y - cam->pos.y) * cam->zoom + ((float)cam->height / 2);
    return screen;
}

void moveCamera(Camera* cam, float dt) {
    const bool *key_states = SDL_GetKeyboardState(NULL);

    float move = cam->speed * dt / cam->zoom;

    if (key_states[SDL_SCANCODE_LSHIFT]) {
        move *= 2.0f;
    } else {
        move /= 2.0f;
    }

    if (key_states[SDL_SCANCODE_W]) cam->pos.y -= move;
    if (key_states[SDL_SCANCODE_S]) cam->pos.y += move;

    if (key_states[SDL_SCANCODE_A]) cam->pos.x -= move;
    if (key_states[SDL_SCANCODE_D]) cam->pos.x += move;
}

void zoomCamera(Camera* cam, float dt) {
    const bool *key_states = SDL_GetKeyboardState(NULL);
    const float zoomSpeed = 1.0f;

    if (key_states[SDL_SCANCODE_Q]) cam->zoom *= expf(+zoomSpeed * dt);
    if (key_states[SDL_SCANCODE_E]) cam->zoom *= expf(-zoomSpeed * dt);
}
