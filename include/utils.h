#ifndef _UTILS_H
#define _UTILS_H

// Utility
void begin2D();
void end2D();
void drawString(const unsigned char *, float, float);
double gettime();
float getDistance2Df(float, float, float, float);
const unsigned char *getEndText(S_uint32_t);
inline _Bool canRender(float xx, float zz) {
    return getDistance2Df(xx, zz, x, z) < renderDistance;
}
inline float squaref(float n) {
    return n * n;
}
void checkError_(const char*, int);
void restartGame();
void resetEverything();
_Bool endsWith(const char*, const char*);

#endif
