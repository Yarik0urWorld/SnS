#include "all.h"

bullet_t enemyPhys[ENEMY_COUNT];

// Enemy logic
void resetEnemyPhys() {
    for (S_uint32_t i = 0; i < ENEMY_COUNT; i++) {
        do {
            enemyPhys[i].x = rand() % (SNOWMAN_MATRIX_SIZE_X * SNOWMAN_MATRIX_DENSITY);
            enemyPhys[i].z = rand() % (SNOWMAN_MATRIX_SIZE_Z * SNOWMAN_MATRIX_DENSITY);
        } while (getDistance2Df(x, z, enemyPhys[i].x, enemyPhys[i].z) < 20.0f);
        enemyPhys[i].lx = 0;
        enemyPhys[i].lz = 0;
        enemyPhys[i].enabled = 1;
        enemyPhys[i].flew = -INFINITY;
        enemyPhys[i].angle = NAN;

        enemyPhys[i].speed = ENEMY_SPEED;
        enemyPhys[i].maxDist = ENEMY_MAX_DIST;
    }
}


void allEnemyTarget(float targetX, float targetZ) {
    for (S_uint32_t i = 0; i < ENEMY_COUNT; i++) {
        oneEnemyTarget(targetX, targetZ, &enemyPhys[i]);
    }
}

void oneEnemyTarget(float targetX, float targetZ, bullet_t *enemy) {
    float d = getDistance2Df(enemy->x, enemy->z, targetX, targetZ);
    enemy->lx = (targetX - enemy->x) / d;
    enemy->lz = (targetZ - enemy->z) / d;
}
void enemyLogic() {
    float averageEnemy0Distance = 0;
    for (S_uint32_t i = 0; i < ENEMY_COUNT; i++) {
        allEnemyTarget(x, z);
        bulletLogic(&enemyPhys[i]);
        enemyPhys[i].enabled = 1;
        averageEnemy0Distance += getDistance2Df(enemyPhys[0].x, enemyPhys[0].z, enemyPhys[i].x, enemyPhys[i].z);
    }
    averageEnemy0Distance /= ENEMY_COUNT - 1;
    if (averageEnemy0Distance < ENEMY_RADIUS * 5) {
        resetEnemyPhys();
    }
}

void enemyPostLogic() {
    for (S_uint32_t i = 0; i < ENEMY_COUNT; i++) {
        if (getDistance2Df(x, z, enemyPhys[i].x, enemyPhys[i].z) <= ENEMY_RADIUS) {
            end = END_LOSE;
        }
    }
}

// Enemy drawing

void drawOneEnemy() {
    // glColor4f(0.5f, 1.0f, 0.0f, 0.5f);
    //~ glColor3f(0.75f, 0.85f, 0.25f);

    //~ glutSolidSphere(ENEMY_RADIUS, 10, 10);
    //~ mdl_gas();
    drawModel(models[2]);
}

void drawAllEnemy() {
    for (S_uint32_t i = 0; i < ENEMY_COUNT; i++) {
        if (canRender(enemyPhys[i].x, enemyPhys[i].z)) {
            glPushMatrix();

            glTranslatef(enemyPhys[i].x, ENEMY_Y, enemyPhys[i].z);
            drawOneEnemy();

            glPopMatrix();
        }
    }
}
