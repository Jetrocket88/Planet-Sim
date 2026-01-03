#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"

#include "helpers.h"
#include "helpers.c"

#include "body.h"
#include "body.c"

#include "Camera.h"
#include "Camera.c"

#include "trail.h"
#include "trail.c"

#include "units.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    srand(time(NULL));

    SDL_Window *pwindow = create_window("Celestial Simulation", WIDTH, HEIGHT);
    SDL_Renderer *prenderer = create_renderer(pwindow);
    SDL_SetRenderDrawBlendMode(prenderer, SDL_BLENDMODE_BLEND);

    //font stuff
    TTF_Font* font = loadFont("C:\\Windows\\Fonts\\Arial.ttf", 32);
    SDL_Texture* fpsTexture = NULL;
    SDL_FRect fpsRect = {0, 0, 0, 0};

    //fps stuff
    int lastFps = -1;

    size_t nBodies = 2;
    Body *bodies = malloc(nBodies * sizeof(Body));
    bodies[0] = initialiseBody(
        STAR,
        YELLOW,
        1.989e30f,
        (Vec2d){0.0f, 0.0f}, //Au position
        (Vec2d){0.0f, 0.0f}, //Au velocity
        (Vec2d){0.0f, 0.0f}, //Au acceleration
        km_to_au(695700)
    );
    bodies[1] = initialiseBody(
        PLANET,
        GREEN,
        5.972e24f,
        (Vec2d){0.05f, 0.0f}, //Au position
        (Vec2d){-0.000f, 0.000e-1}, //Au velocity
        (Vec2d){0.0f, 0.0f}, //Au acceleration
        km_to_au(6371)
    );

    Camera cam = initialiseCamera(
        (Vec2d){0.0f, 0.0f},
        500.0f,
        WIDTH,
        HEIGHT,
        1000.0f
    );

    bool running = true;
    SDL_Event event;
    Uint32 lastUpdate = SDL_GetTicks();
    while (running) {

        Uint64 start = SDL_GetPerformanceCounter();
        Uint32 current = SDL_GetTicks();
        float dt = (current - lastUpdate) / 1000.0f;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE) {
                    running = false;
                }
                break;
            }
        }
        SDL_SetRenderDrawColor(prenderer, 0, 0, 0, 255);
        SDL_RenderClear(prenderer);

        for(size_t i = 0; i < nBodies; i++) {
            Body* b = &bodies[i];
            if (!b->alive) continue;
            SDL_SetRenderDrawColor(prenderer, b->color.r, b->color.g, b->color.b, 255);

            Vec2d screenPos = worldToScreen(b->pos, &cam);
            double visibleRadius = clamp(b->radius * cam.zoom, 2.0, 1e6);

            drawFilledCircle(prenderer, screenPos.x, screenPos.y, visibleRadius);
            drawTrail(prenderer, &cam, &bodies[0]);
            drawTrail(prenderer, &cam, &bodies[1]);
        }
        SDL_Delay(4);
        updateAllBodies(bodies, nBodies, dt);
        moveCamera(&cam, dt);
        zoomCamera(&cam, dt);

        //physicis
        lastUpdate = current;

        //fps
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        int fps = (int)(1/elapsed);

        if (fps != lastFps) {
            lastFps = fps;
            if (fpsTexture) { SDL_DestroyTexture(fpsTexture); }
            char buffer[32];
            sprintf(buffer, "FPS: %d", fps);
            fpsTexture = createTextTexture(prenderer, font, buffer, &fpsRect, 0);
        }
        if (fpsTexture) { SDL_RenderTexture(prenderer, fpsTexture, NULL, &fpsRect); }
        SDL_RenderPresent(prenderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}
