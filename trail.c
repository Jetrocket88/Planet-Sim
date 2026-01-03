#include "trail.h"

void trailPush(Trail* t, Vec2d pos) {
    t->points[t->trailHead] = pos;
    t->trailHead = (t->trailHead + 1) % MAX_TRAIL_LENGTH;
    if (t->trailCount < MAX_TRAIL_LENGTH) {
        t->trailCount++;
    }
}

Trail* initTrail() {
    Trail* t = malloc(sizeof(Trail));
    assert(t != NULL);
    t->trailHead = 0;
    t->trailCount = 0;
    return t;
}
