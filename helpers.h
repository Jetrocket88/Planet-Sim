#ifndef HELPERS_H
#define HELPERS_H

#include <SDL3/SDL.h>
#include "SDL3_ttf/SDL_ttf.h"

#include <stdlib.h>
#include <stdio.h>

#include "math.h"

#define WIDTH 1920 
#define HEIGHT 1080 
#define G 6.67430e-11f // Gravitational constant
#define SQUARE(x) ((x) * (x))
#define MIL 1000000 
#define CENTER_W WIDTH / 2.0f
#define CENTER_H HEIGHT / 2.0f

#define YELLOW (SDL_Color){255, 255, 0, 255}
#define GREEN (SDL_Color) {0, 255, 0, 255}
#define WHITE (SDL_Color){255, 255, 255, 255}

typedef struct {
    double x;
    double y;
} Vec2d; 

SDL_Window* create_window(const char* title, int width, int height);
SDL_Renderer* create_renderer(SDL_Window* window);
TTF_Font* loadFont(const char* path, size_t fontSize);
SDL_Texture* createTextTexture(SDL_Renderer* prenderer, TTF_Font* font, const char* text, SDL_FRect* outRect, size_t len);

void drawCircle(int x, int y, int radius, SDL_Renderer* renderer);
void drawFilledCircle(SDL_Renderer *renderer, double cx, double cy, double radius);
void drawLine(SDL_Renderer* renderer, SDL_Color color, Vec2d start, Vec2d end);

double clamp(double val, double min, double max);

float randFloatRange(float min, float max);

#endif // HELPERS_H 

