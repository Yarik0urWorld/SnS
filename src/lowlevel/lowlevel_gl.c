#include <GL/gl.h>

#include "all.h"

float angle = 0.0;
float lx = 0.0f, lz = -1.0f;
float x = SNOWMAN_MATRIX_SIZE_X * SNOWMAN_MATRIX_DENSITY / 2, z = SNOWMAN_MATRIX_SIZE_Z * SNOWMAN_MATRIX_DENSITY / 2;
float deltaAngle = 0.0f;
float deltaMove = 0;
double t_begin = 0, t_end = 0, frame_begin = 0, tpf = 0.16f;
int width, height;
S_uint32_t DynaSBF_degree = 1;
S_uint32_t stableFPS = 0;
S_uint32_t stableFPSCounter = 0;
double lastStableFPSUpdate = 0;
S_uint32_t quality = 1;
float renderDistance = 50.0f;
#ifdef DEBUG_FEATURES
_Bool upperView = 0;
#endif

// GL handling & (kinda) physics (Lowlevel)
void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0f / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

    width = w;
    height = h;
}


void computePos(float deltaMove) {
    register float x1 = x + deltaMove * lx * 0.1f, z1 = z + deltaMove * lz * 0.1f;
	
    if (collidesSnowman(x1, z1) == bin) {
        x = x1; z = z1;
    }
}
 
void computeDir(float deltaAngle) {
	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

void fixPosition() {    // Requires resetSnowmanMatrix
    while(collidesSnowman(x, z) != bin) {
        x -= 0.1f;
        z -= 0.1f;
    }
}

