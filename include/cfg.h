// It's a config file. Comment / uncomment #defines to configure the game.

#ifndef _CFG_H
#define _CFG_H

//~ #define DEBUG_FEATURES    // Uses GLU, GLU is forbidden in this game
//~ #define STAB_IFS          // Debug stablisation
#define GL_ERRORS_ARE_FATAL
#define RENDER_DISTANCE       // Notice: if RENDER_DISTANCE is on, GPU will work less, but processor will work a bit more!
#define WINDOWS1251               // Windows-1251 support
//~ #define ENABLE_PACK           // It's easier to access unpacked structures I guess, but they're taking more memory, so that's the switch

#endif
