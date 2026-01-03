#ifndef TRAIL_H
#define TRAIL_H

#include "helpers.h"
#include <assert.h>

#define MAX_TRAIL_LENGTH 2000

typedef struct {
    Vec2d points[MAX_TRAIL_LENGTH];
    size_t trailHead; //the head to write to 
    size_t trailCount; //how many points are in the trail
} Trail;


void trailPush(Trail* t, Vec2d pos);
Trail* initTrail();


#endif //TRAIL_H

