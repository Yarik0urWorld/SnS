#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include "all.h"

// Appearance
S_uint32_t end = 0;
_Bool helpOpened = 1;

void renderScene() {
    frame_begin = gettime();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.6f, 0.85f, 0.91f, 1.0f);
    
	glLoadIdentity();

    if (helpOpened) {
        // glMatrixMode(GL_PROJECTION);
        // glPushMatrix();
        // glLoadIdentity();
        // glMatrixMode(GL_MODELVIEW);
        
        // glDisable(GL_DEPTH_TEST);
        // loadTexture();
        // glBindTexture(GL_TEXTURE_2D, texture);
        // glBegin(GL_QUADS);
        //     glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
        //     glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f);
        //     glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
        //     glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
        // glEnd();
        // glBindTexture(GL_TEXTURE_2D, 0);
        // glEnable(GL_DEPTH_TEST);

        // glMatrixMode(GL_PROJECTION);
        // glPopMatrix();
        // glMatrixMode(GL_MODELVIEW);
        glColor3f(0.0f, 0.0f, 0.0f);
        snprintf(&buf[0], BUF_SZ, "Use W/S keys to walk,");
        drawString(&buf[0], -1.0f,  0.9f);
        snprintf(&buf[0], BUF_SZ, "A/D to look around.");
        drawString(&buf[0], -1.0f,  0.8f);
        snprintf(&buf[0], BUF_SZ, "Space to shoot.");
        drawString(&buf[0], -1.0f,  0.7f);
        snprintf(&buf[0], BUF_SZ, "Press H if you're stuck");
        drawString(&buf[0], -1.0f,  0.6f);
        snprintf(&buf[0], BUF_SZ, "in a snowman.");
        drawString(&buf[0], -1.0f,  0.5f);
        snprintf(&buf[0], BUF_SZ, "Use [ and ] keys to");
        drawString(&buf[0], -1.0f,  0.4f);
        snprintf(&buf[0], BUF_SZ, "reduce and increase");
        drawString(&buf[0], -1.0f,  0.3f);
        snprintf(&buf[0], BUF_SZ, "quality, respectively.");
        drawString(&buf[0], -1.0f,  0.2f);
        snprintf(&buf[0], BUF_SZ, "Use - and = keys to");
        drawString(&buf[0], -1.0f,  0.1f);
        snprintf(&buf[0], BUF_SZ, "reduce and increase");
        drawString(&buf[0], -1.0f,  0.0f);
        snprintf(&buf[0], BUF_SZ, "render distance, respectively.");
        drawString(&buf[0], -1.0f, -0.1f);
        snprintf(&buf[0], BUF_SZ, "Aware of green gas! It will");       // I think it'll be better if I'll type here "green gas" rather than "green ememy"
        drawString(&buf[0], -1.0f, -0.2f);
        snprintf(&buf[0], BUF_SZ, "kill you immediately.");
        drawString(&buf[0], -1.0f, -0.3f);
        snprintf(&buf[0], BUF_SZ, "Green gas also destroys snowmen.");
        drawString(&buf[0], -1.0f, -0.4f);
        snprintf(&buf[0], BUF_SZ, "Press F1 to dimiss this help.");
        drawString(&buf[0], -1.0f, -0.5f);
        snprintf(&buf[0], BUF_SZ, "When game starts, try to run away.");
        drawString(&buf[0], -1.0f, -0.7f);
        snprintf(&buf[0], BUF_SZ, "Your target - destroy all snowmen.");
        drawString(&buf[0], -1.0f, -0.8f);

    } else {

        computePos(deltaMove * !end * tpf);
        computeDir(deltaAngle * !end * tpf);

        gunLogic();
        bulletLogic(&bullet);
        if (!end) {
            enemyLogic();
        }


#ifdef DEBUG_FEATURES
            gluLookAt(	x,                     EYE_Y + 10 * upperView,   z,
                        x + lx * !upperView,   EYE_Y,                    z + lz * !upperView,
                        0.0f, 1 - upperView,   upperView	);
#else
            // gluLookAt(	x,      EYE_Y,  z,
                        // x+lx,   EYE_Y,  z+lz,
                        // 0.0f,   1.0f,   0.0f	);
            glRotatef(RADTODEG(angle), 0.0f, 1.0f, 0.0f);
            glTranslatef(-x, -EYE_Y, -z);
#endif

        glColor3f(0.9f, 0.9f, 0.9f);
        
        glBegin(GL_QUADS);
            glVertex3f(-10000.0f, 0.0f, -10000.0f);
            glVertex3f(-10000.0f, 0.0f,  10000.0f);
            glVertex3f( 10000.0f, 0.0f,  10000.0f);
            glVertex3f( 10000.0f, 0.0f, -10000.0f);
        glEnd();

        if (end) {

            if (t_end + T_EXIT_AFTER_WIN < gettime()) exit(0);

        } else {
            drawAllEnemy();

            register int currentHP;
            snowmenLeft = 0;

            for (unsigned int z = 0; z < SNOWMAN_MATRIX_SIZE_Z; z++)
                for (unsigned int x = 0; x < SNOWMAN_MATRIX_SIZE_X; x++){
                    currentHP = snowmanMatrix[z][x];

                    if (currentHP <= 0) continue;
                    snowmenLeft++;
#ifdef RENDER_DISTANCE
                    if (canRender(x * SNOWMAN_MATRIX_DENSITY, z * SNOWMAN_MATRIX_DENSITY)) {
#endif
                        glPushMatrix();
                
                        glTranslatef(x * SNOWMAN_MATRIX_DENSITY, 0, z * SNOWMAN_MATRIX_DENSITY);
                
                        // Hitboxes
                        // ~ glColor3f(0.5f, 1.0f, 0.5f);
                        //~ glBegin(GL_QUADS);
                            // ~ glVertex3f(-0.5f, 2.0f, -0.5f);
                            //~ glVertex3f(-0.5f, 2.0f,  0.5f);
                            //~ glVertex3f( 0.5f, 2.0f,  0.5f);
                            //~ glVertex3f( 0.5f, 2.0f, -0.5f);
                        //~ glEnd();
            
                        drawSnowMan(currentHP);
            
                        glPopMatrix();
#ifdef RENDER_DISTANCE
                    }
#endif
            }

            drawBullet();
            drawGun();
            
            enemyPostLogic();

            if (end == NO_END) end = !snowmenLeft * END_WIN;

            if (end) {
                t_end = gettime();
            }
        }

        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

        snprintf(&buf[0], BUF_SZ, "%.1f s; x:%.1f; z:%.1f; %d FPS; %dx%d", gettime() * !end + t_end * !!end - t_begin, x, z, stableFPS, height, width);
        drawString(&buf[0], -1.0f, 0.9f);

        snprintf(&buf[0], BUF_SZ, "DynaSBF:%d; quality:%d; render distance:%.f", DynaSBF_degree, quality, renderDistance);
        drawString(&buf[0], -1.0f, 0.8f);

        snprintf(&buf[0], BUF_SZ, "snowmen left:%d enemy0 x:%.1f enemy0 z:%.1f", snowmenLeft, enemyPhys[0].x, enemyPhys[0].z);
        drawString(&buf[0], -1.0f, 0.7f);

        drawString(getEndText(end), -0.5f, 0.1f);

        snprintf(&buf[0], BUF_SZ, "Press ESC to exit, or");
        buf[0] *= !!end;
        drawString(&buf[0], -0.5f, 0.0f);
        snprintf(&buf[0], BUF_SZ, "R to reset . . .");
        buf[0] *= !!end;
        drawString(&buf[0], -0.5f, -0.1f);
        
        begin2D();
        glBegin(GL_LINES);
            glVertex2f(-20.0f / width,  0.0f / height);
            glVertex2f( 20.0f / width,  0.0f / height);
            glVertex2f(  0.0f / width, -20.0f / height);
            glVertex2f(  0.0f / width,  20.0f / height);
        glEnd();
        end2D();
    }

    checkError();
	glutSwapBuffers();

    // Debug
    // printf("\nx=%.1f z=%.1f\n", x, z);
    // for (S_uint32_t xx = 0; xx < SNOWMAN_MATRIX_SIZE_X; xx++) {
    //     for (S_uint32_t zz = 0; zz < SNOWMAN_MATRIX_SIZE_Z; zz++) {
    //         if (collidesSnowman(x, z) != bin) printf("[%ld] ", snowmanMatrix[zz][xx]);
    //         else printf(" %ld  ", snowmanMatrix[zz][xx]);
    //     }
    //     printf ("\n");
    // }

    tpf = gettime() - frame_begin;
    stableFPSCounter++;
    lastStableFPSUpdate += tpf;
    if (lastStableFPSUpdate >= 1.0) {
        lastStableFPSUpdate = 0.0;
        stableFPS = stableFPSCounter;
        stableFPSCounter = 0;
    }

}
