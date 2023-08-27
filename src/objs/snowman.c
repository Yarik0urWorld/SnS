#include <GL/gl.h>

#include "all.h"

long snowmanMatrix[SNOWMAN_MATRIX_SIZE_Z][SNOWMAN_MATRIX_SIZE_X];
S_uint32_t snowmenLeft = SNOWMAN_MATRIX_SIZE_X * SNOWMAN_MATRIX_SIZE_Z;

// Snowmen logic
void resetSnowmanMatrix() {
    for (unsigned int z = 0; z < SNOWMAN_MATRIX_SIZE_Z; z++) {
        for (unsigned int x = 0; x < SNOWMAN_MATRIX_SIZE_X; x++) {
            snowmanMatrix[z][x] = RAND_MAX / 2 < rand() ? SNOWMAN_MAX_HP : 0;
        }
    }
}

long *collidesSnowman(float x, float z) {
    int snx, snz; // Nearest snowman x and z in snowman matrix

    // Get nearest snowman position 
    snx = round(x / SNOWMAN_MATRIX_DENSITY);
    snz = round(z / SNOWMAN_MATRIX_DENSITY);

    // Check whether given position is too far away
    if ( !(snx > SNOWMAN_MATRIX_SIZE_X || snx < 0 || snz > SNOWMAN_MATRIX_SIZE_Z || snz < 0) ) { 

        // If distance to nearest snowman is smaller or equal to SNOWMAN_RADIUS...
        if (getDistance2Df(x, z, snx * SNOWMAN_MATRIX_DENSITY, snz * SNOWMAN_MATRIX_DENSITY) <= SNOWMAN_RADIUS) {
            // and the snowman isn't already destroyed, (x, z) collides snowman.
            if (snowmanMatrix[snz][snx] > 0) {
                return &snowmanMatrix[snz][snx];
            }
        }
    }

    return bin;
}

// Snowmen drawing
void drawSnowMan(long health) {
#ifdef STAB_IFS
    if (health <= 0) return;
#endif

 	glColor3f(1.0f, 1.0f, 1.0f);
 	
    // Snowman's body
	//~ glTranslatef(0.0f, 0.75f, 0.0f);
	//~ glutSolidSphere(0.75f, (quality + 1) * 10, (quality + 1) * 10);
	//~ mdl_snowmanBody(); //  <====== HERE
	drawModel(models[0]);
 	
    // Snowman's head
	//~ glTranslatef(0.0f, 1.0f * ( ((float) health - 1) / (SNOWMAN_MAX_HP - 1) * (1 - SNOWMAN_HEAD_MIN_HEIGHT) + SNOWMAN_HEAD_MIN_HEIGHT), 0.0f); //  <====== HERE
	//~ glutSolidSphere(0.25f, (quality + 1) * 7, (quality + 1) * 7);
	//~ mdl_snowmanHead(); //  <====== HERE
	
    // Snowman's eyes
	//~ glPushMatrix();
	//~ glColor3f(0.0f, 0.0f, 0.0f);
	//~ glTranslatef(0.05f, 0.10f, 0.18f);
	//~ glutSolidSphere(0.05f, (quality + 1) * 4, (quality + 1) * 4);
	//~ glTranslatef(-0.1f, 0.0f, 0.0f);
	//~ glutSolidSphere(0.05f, (quality + 1) * 4, (quality + 1) * 4);
	//~ glPopMatrix();
    
	// Snowman's nose
	//~ glColor3f(1.0f, 0.5f , 0.5f);
	//~ glutSolidCone(0.08f, 0.5f, quality * 5, 2);
}
