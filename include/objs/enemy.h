#ifndef _ENEMY_H
#define _ENEMY_H

#include "vars.h"

// Enemy logic
void resetEnemyPhys();
void allEnemyTarget(float, float);
void oneEnemyTarget(float, float, bullet_t *);
void enemyLogic();
void enemyPostLogic();

// Enemy drawing
void drawOneEnemy();
void drawAllEnemy();

#endif

