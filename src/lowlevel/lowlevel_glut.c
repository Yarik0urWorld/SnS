#include <GL/gl.h>
#include <GL/glut.h>

#include "all.h"

// GLUT stuff

void pressKey(int key, int xx, int yy) {
 
	switch (key) {

        case GLUT_KEY_F1:
            helpOpened = !helpOpened;
            break;
	}
}
 
void releaseKey(int key, int x, int y) {}

void pressNormalKey(unsigned char key, int x, int y) {
    switch (key) {
#ifdef _1251
		case 0xF4:
#endif
        case 'a':
            deltaAngle = -RSPEED;
            break;
#ifdef _1251
		case 0xE2:
#endif
        case 'd':
            deltaAngle = RSPEED;
            break;
#ifdef _1251
		case 0xF6:
#endif
        case 'w':
            deltaMove = SPEED;
            break;
#ifdef _1251
		case 0xFB:
#endif
        case 's':
            deltaMove = -SPEED;
            break;
        case ' ':
            shoot();
            break;
#ifdef DEBUG_FEATURES
#ifdef _1251
		case 0xE3:
#endif
        case 'u':
            upperView = !upperView;
            break;
#endif
#ifdef _1251
		case 0xFA:
#endif
        case ']':
            quality++;
            break;
#ifdef _1251
		case 0xF5:
#endif
        case '[':
            if (quality > 1) quality--;
            break;
        case '-':
            renderDistance -= 10.0f;
            if (renderDistance < 20.0f) renderDistance = 20.0f;
            break;
        case '=':
            renderDistance += 10.0f;
            break;
        case 27:
            exit(0);
            break;
#ifdef _1251
		case 0xEA:
#endif
        case 'r':
			if (end) {
				resetEverything();
			}
    }
}

void releaseNormalKey(unsigned char key, int xx, int yy) {
    switch (key) {
#ifdef _1251
		case 0xF4:
		case 0xE2:
#endif
        case 'a':
        case 'd': 
            deltaAngle = 0.0f;
            break;
#ifdef _1251
		case 0xF6:
		case 0xFB:
#endif
        case 'w':
        case 's': 
            deltaMove = 0;
            break;
#ifdef _1251
		case 0xF0:
#endif
        case 'h':
            fixPosition();
            break;
    }
}


// Comletely broken in GLUT (thus I'd like to use glX/wgl for framework purposes)
//~ void passiveMotionFunc(int x, int y) {
    //~ deltaAngle = (float)(width / 2 - x) / width * RSPEED;
    //~ glutWarpPointer(width / 2, height / 2);
    //~ printf("%f\n", deltaAngle);
    //~ glutPostRedisplay();
//~ }
