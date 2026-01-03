#include "helpers.h"
#include <stdint.h>

SDL_Window *create_window(const char *title, int width, int height) {
    SDL_Window *window =
        SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Could not create window: %s\n", SDL_GetError());
    }
    return window;
}

SDL_Renderer *create_renderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        printf("Could not create renderer: %s\n", SDL_GetError());
    }
    return renderer;
}

void drawCircle(int x, int y, int radius, SDL_Renderer *basic_renderer) {
    for (int i = 0; i < 360; i++) {
        float xc = (float)WIDTH / 2;
        float yc = (float)HEIGHT / 2;

        x = xc + radius * cos(i);
        y = yc + radius * sin(i);
        SDL_RenderPoint(basic_renderer, x, y);
    }
    SDL_RenderPresent(basic_renderer);
}

void drawFilledCircle(SDL_Renderer *renderer, double cx, double cy, double radius) {
    for (double y= -radius; y <= radius; y++) {
        double dx = (double)sqrt(radius * radius - y * y);
        SDL_RenderLine(renderer, cx - dx, cy + y, cx + dx, cy + y);
    }
}

float randFloatRange(float min, float max) {
    float scale = rand() / (float)RAND_MAX; // [0, 1.0]
    return min + scale * (max - min);       // [min, max]
}

double clamp(double val, double min, double max) {
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    }
    return val;
}

TTF_Font* loadFont(const char* path, size_t fontSize) {
    TTF_Font* font = TTF_OpenFont(path, fontSize);
    if (!font) {
        printf("Failed to load font: %s\n", SDL_GetError());
        return NULL;
    }
    return font;
}

SDL_Texture* createTextTexture(
    SDL_Renderer* prenderer,
    TTF_Font* font,
    const char* text,
    SDL_FRect* outRect,
    size_t len
) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, len, WHITE);
    if (!surface) return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(prenderer, surface);
    SDL_DestroySurface(surface);
    SDL_GetTextureSize(texture, &outRect->w, &outRect->h);
    return texture;
}

void drawLine(SDL_Renderer* renderer, SDL_Color colour, Vec2d start, Vec2d end) {
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);
}

void updateTimeScale(float* timeScale, float* timeScaleArray, size_t len, size_t* currentIndex) {
    const bool *key_states = SDL_GetKeyboardState(NULL);
    Uint32 now = SDL_GetTicks();
    static Uint32 lastPress = 0;
    Uint32 elapsed = now - lastPress;



    if (key_states[SDL_SCANCODE_UP] && elapsed > 200) {
        *currentIndex = (*currentIndex + 1) % len;
        *timeScale = timeScaleArray[*currentIndex];
        lastPress = SDL_GetTicks();
    }
    if (key_states[SDL_SCANCODE_DOWN] && elapsed > 200) {
        *currentIndex = (*currentIndex - 1) % len;
        *timeScale = timeScaleArray[*currentIndex];
        lastPress = SDL_GetTicks();
    }
    return;
}
