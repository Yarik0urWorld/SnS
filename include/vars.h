#ifndef _VARS_H
#define _VARS_H

#include <inttypes.h>
#include <GL/gl.h>

#include "defs.h"

// Here are all the variables and S_uint32_t (TODO: REMOVE IT)

typedef uint32_t S_uint32_t;

typedef struct PACK _bullet {
    float x, z, lx, lz, flew, angle, maxDist, speed;
    _Bool enabled;
} bullet_t;

extern float angle;
extern float lx, lz;
extern float x, z;
extern float deltaAngle;
extern float deltaMove;
extern float gunReload;
extern bullet_t bullet;
extern long snowmanMatrix[SNOWMAN_MATRIX_SIZE_Z][SNOWMAN_MATRIX_SIZE_X];
extern _Bool helpOpened;
//~ extern _Bool textureLoaded;
//~ extern GLuint texture;
extern double t_begin, t_end, frame_begin, tpf;
extern unsigned char buf[BUF_SZ];
extern int width, height;
extern S_uint32_t DynaSBF_degree;
extern void *bin;                      // IF killer
extern S_uint32_t stableFPS;
extern S_uint32_t stableFPSCounter;
extern double lastStableFPSUpdate;
extern S_uint32_t end;
extern S_uint32_t quality;
extern S_uint32_t snowmenLeft;
extern float renderDistance;
extern bullet_t enemyPhys[ENEMY_COUNT];

#endif
