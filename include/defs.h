/*
 * This file contains all numeric constants and #define functions
 */

#ifndef _DEFS_H
#define _DEFS_H

// Idk if _USE_MATH_DEFINES does something on Linux or Mac
#define _USE_MATH_DEFINES
#include <math.h>

#include "cfg.h"

// Movement
#define SPEED 180.0f
#define RSPEED 3.0f
#define EYE_Y 1.0f

// Gun
#define GUN_ROT M_PI_4 / 3
#define GUNRELOAD_MAX 0.1f
#define GUNRELOAD_TIME 0.16f
#define GUN_DAMAGE 1

// Bullet
#define BULLET_Y EYE_Y - 0.3f
#define BULLET_SPEED 60.0f
#define BULLET_MAX_DIST 20.0f
#define DYNASBF_Q 50                 // DynaSBF = Dynamic SBF; SBF = Smooth Bullet Flight

// Enemy
#define ENEMY_SPEED 5.0f         // 5.0f (may be set to 0 for debug)
#define ENEMY_MAX_DIST INFINITY
#define ENEMY_COUNT 5
#define ENEMY_RADIUS 1.0f

// Snowman
#define SNOWMAN_MATRIX_SIZE_X 10
#define SNOWMAN_MATRIX_SIZE_Z 10
#define SNOWMAN_MATRIX_DENSITY 5
#define SNOWMAN_RADIUS 1.0f
#define SNOWMAN_MAX_HP 3

// Snowman model
#define SNOWMAN_HEAD_MIN_HEIGHT 0.75f

// Arrow model
#define ARROW_SIZE 0.02f
#define ARROW_LENGTH 1.5f
#define ARROWHEAD_Z 0.2f
#define ARROWHEAD_XS 0.1f
#define ARROWHEAD_YS 0.03f

// Bow model
#define BOW_THICKNESS 0.03f
#define BOWBODY_FRONT_LN 0.3f
#define BOWBODY_CURVE_OFFSET 0.2f
#define BOWBODY_CURVE_LN 0.7f
#define BOW_HOLE_THICKNESS 0.025f
#define BOWSPRING_MAX_TENSION 0.2f

// Enemy model
#define ENEMY_Y 1.5f

// Ending types
#define NO_END 0
#define END_WIN 1
#define END_LOSE 2

// Misc
#define FONT GLUT_BITMAP_8_BY_13
#define BUF_SZ 256
#define T_EXIT_AFTER_WIN 10
#define VERSION "0.3.1-dev231009"      //

// Models
#define MODEL_COUNT 1000

// Logs
#define LOGLEVEL_FATAL 0
#define LOGLEVEL_ERROR 1
#define LOGLEVEL_WARN  2
#define LOGLEVEL_INFO  3
#define LOGLEVEL_DEBUG 4

// see "man ls" for example for more info
#define LOGCOLOR_ALWAYS 0
#define LOGCOLOR_NEVER  1
#define LOGCOLOR_AUTO   2

// Mouse
#define POINTER_BORDER_WIDTH 50

#if defined(WINDOWS1251) && defined(_WIN32)
#	 define _1251
#endif

// Functions
#ifdef ENABLE_PACK
#    if defined(__GCC__)
#        define PACK __attribute__((__packed__))
#    elif defined(__clang__)
#        define PACK __attribute__((packed))
#    else
#        define PACK
#    endif
#else
#    define PACK
#endif

#define checkError() checkError_(__FILE__, __LINE__)
#define logMessage(lvl, str) logMessage_(__FILE__, __LINE__, lvl, str) 
#define RADTODEG(x) ((x) * 57.29577951308232)

#endif
