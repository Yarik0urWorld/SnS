#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

#include "all.h"

unsigned char buf[BUF_SZ];
void *bin;                      // IF killer

void begin2D() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
    glDisable(GL_DEPTH_TEST);
}
void end2D() {
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// Utility
void drawString(const unsigned char *s, float x, float y) {
    begin2D();

    glRasterPos2f(x, y);
    for (const unsigned char *c = s; *c != '\0'; c++) {
        glutBitmapCharacter(FONT, *c);
    }
    
    end2D();
}

#ifdef _WIN32
double gettime() {
    FILETIME ft;
    
    GetSystemTimeAsFileTime(&ft);
    
    return (double)((ft.dwHighDateTime & 0x7f) << 25 | ft.dwLowDateTime >> 7) / 78125;
}
#else
double gettime() {
    struct timeval t;

    gettimeofday(&t, 0);
    return ((double)t.tv_usec)/ 1000000 + t.tv_sec;
}
#endif

void checkError_(const char *file, int line)
{
    GLenum errorCode;
    S_uint32_t errorsOccurred = 0;
	FILE* s_stderr;
#ifdef _WIN32
	s_stderr = fopen("errlog.txt", "w");
#else
	s_stderr = stderr;
#endif
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {

        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  strcpy(buf, "GL_INVALID_ENUM"); break;
            case GL_INVALID_VALUE:                 strcpy(buf, "GL_INVALID_VALUE"); break;
            case GL_INVALID_OPERATION:             strcpy(buf, "GL_INVALID_OPERATION"); break;
            case GL_STACK_OVERFLOW:                strcpy(buf, "GL_STACK_OVERFLOW"); break;
            case GL_STACK_UNDERFLOW:               strcpy(buf, "GL_STACK_UNDERFLOW"); break;
            case GL_OUT_OF_MEMORY:                 strcpy(buf, "GL_OUT_OF_MEMORY"); break;
//            case GL_INVALID_FRAMEBUFFER_OPERATION: strcpy(buf, "GL_INVALID_FRAMEBUFFER_OPERATION"); break;
        }
        errorsOccurred++;

        fprintf(s_stderr, "OpenGL error %s occurred at file %s at line %d\n", buf, file, line);
    }

#ifdef GL_ERRORS_ARE_FATAL
    if (errorsOccurred) {
#ifdef _WIN32
		snprintf(&buf[0], BUF_SZ, "%d error(s) occurred. Exiting.\n", errorsOccurred);
        MessageBoxA(NULL, &buf[0], "OpenGL Error(s)", MB_ICONERROR);
#else
		fprintf(s_stderr, "%d error(s) occurred. Exiting.\n", errorsOccurred);
#endif
		exit(1);
    }
#endif

#ifdef _WIN32
    fclose(s_stderr);
#endif
}

// Utility
float getDistance2Df(float x1, float y1, float x2, float y2) {
    return sqrt(squaref(x1 - x2) + squaref(y1 - y2));
}


const unsigned char *getEndText(S_uint32_t endType) {
    switch (endType) {
        case NO_END:
            strcpy(buf, "");
            break;
        case END_WIN:
            strcpy(buf, "You win!");
            break;
        case END_LOSE:
            strcpy(buf, "You lose!");
            break;
    }

    return &buf[0];
}

_Bool endsWith(const char *string, const char *suffix) {
    size_t str_size = strlen(string);
    size_t suffix_size = strlen(suffix);
    
    if (str_size < suffix_size) return 0;
    
    return strncmp(string + str_size - suffix_size, suffix, suffix_size) == 0;
}

void resetEverything() {
    DynaSBF_degree = 1;
	stableFPS = 0;
	stableFPSCounter = 0;
	lastStableFPSUpdate = 0;
	quality = 1;
    renderDistance = 50.0f;
    restartGame();
}

void restartGame() {
    // vars copypasted from 0.2-legacy main.c
	angle = 0.0;
	lx = 0.0f; lz = -1.0f;
	x = SNOWMAN_MATRIX_SIZE_X * SNOWMAN_MATRIX_DENSITY / 2;
    z = SNOWMAN_MATRIX_SIZE_Z * SNOWMAN_MATRIX_DENSITY / 2;
	deltaAngle = 0.0f;
	deltaMove = 0;
	gunReload = 0.0f;
	//~ helpOpened = 1;
	// _Bool textureLoaded = 0;
	// GLuint texture;
	t_begin = gettime(); t_end = 0; frame_begin = 0; tpf = 0.16f;
	//~ DynaSBF_degree = 1;
	//~ stableFPS = 0;
	//~ stableFPSCounter = 0;
	//~ lastStableFPSUpdate = 0;
	end = 0;
	//~ quality = 1;
	snowmenLeft = SNOWMAN_MATRIX_SIZE_X * SNOWMAN_MATRIX_SIZE_Z;
	//~ renderDistance = 50.0f;
	
	srand(time(NULL));
    resetBullet();
    resetSnowmanMatrix();
    resetEnemyPhys();
    fixPosition();
}

//~ inline _Bool canRender(float xx, float zz) {
    //~ return getDistance2Df(xx, zz, x, z) < renderDistance;
//~ }
//~ inline float squaref(float n) {
    //~ return n * n;
//~ }
