#include "all.h"

// Bullet type
void bulletStep(bullet_t *b) {
    // Destruct bullet if it flew too much
    if (b->flew >= b->maxDist) b->enabled = 0;
    if (!b->enabled) return;
    
    *((long *) bin) = 0;
    (*collidesSnowman(b->x, b->z)) -= GUN_DAMAGE;

    b->enabled = *((long *) bin) != 0;

    b->x += b->lx * b->speed * tpf / DynaSBF_degree;
    b->z += b->lz * b->speed * tpf / DynaSBF_degree;
    b->flew += b->speed * tpf / DynaSBF_degree;
}

void bulletLogic(bullet_t *b) {
    DynaSBF_degree = tpf * DYNASBF_Q + 1;

    for (S_uint32_t i = 0; i < DynaSBF_degree; i++) {
        bulletStep(b);
    }
}
