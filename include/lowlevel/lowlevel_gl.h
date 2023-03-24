#ifndef _LOWLEVEL_GL_H
#define _LOWLEVEL_GL_H

#include "defs.h" // for DEBUG_FEATURES

// GL handling & (kinda) physics (Lowlevel)
void changeSize(int, int);
void computePos(float);
void computeDir(float);
void fixPosition();

#endif
