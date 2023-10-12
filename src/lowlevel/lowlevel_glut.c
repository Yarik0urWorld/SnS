#include <GL/gl.h>
#include <GL/glut.h>

#include "all.h"

// GLUT stuff

int last_x, last_y;
_Bool warped_pointer = 0;

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
				restartGame();
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
void passiveMotionFunc(int x, int y) {
    if (!warped_pointer) {
		deltaAngle = (float)(x - last_x)/ width * RSPEED * 100;
		printf("%f, %d %d, %d %d, %d %d\n", deltaAngle, x, y, last_x, last_y, x - last_x, y - last_y); 
		last_x = x;
		last_y = y;
	}
    if (x < POINTER_BORDER_WIDTH || y < POINTER_BORDER_WIDTH || x > width-POINTER_BORDER_WIDTH || y > height-POINTER_BORDER_WIDTH) {
		glutWarpPointer(width / 2, height / 2);
		last_x = width / 2;
		last_y = height / 2;
		warped_pointer = 1;
	} else warped_pointer = 0;
    glutPostRedisplay();
}
