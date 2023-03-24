#include <GL/gl.h>

#include "all.h"

// Bullet logic
void resetBullet() {
    bullet.x = 0;
    bullet.z = 0;
    bullet.lx = 0;
    bullet.lz = 0;
    bullet.enabled = 0;
    bullet.flew = 0;
    bullet.angle = 0;

    bullet.speed = BULLET_SPEED;
    bullet.maxDist = BULLET_MAX_DIST;
}

void shoot() {
    
    if (gunReload == 0.0f && bullet.enabled == 0) {
        bullet.x = x;
        bullet.z = z;
        bullet.lx = lx;
        bullet.lz = lz;
        bullet.angle = angle; // needed for arrow drawing
        bullet.enabled = 1;
        bullet.flew = 0;
        
        gunReload = GUNRELOAD_MAX;
    }
}

bullet_t bullet;

// Bullet drawing
void drawBullet() {
    if (!bullet.enabled) return;
    
    glPushMatrix();
    
    glTranslatef(bullet.x, BULLET_Y, bullet.z);
    glRotatef(180 - RADTODEG(bullet.angle), 0.0f, 1.0f, 0.0f);
        
    glColor3f(0.45f, 0.29f, 0.19f);
    
    // Arrow body
    
    /* /\
     * \/
     */
    glBegin(GL_QUADS);
        /* \ 
         * 
         */
        glVertex3f( 0.0f,        ARROW_SIZE,  0.0f        );
        glVertex3f( ARROW_SIZE,  0.0f,        0.0f        );
        glVertex3f( ARROW_SIZE,  0.0f,       -ARROW_LENGTH);
        glVertex3f( 0.0f,        ARROW_SIZE, -ARROW_LENGTH);
        
        /* 
         *  /
         */
        glVertex3f( ARROW_SIZE,  0.0f,       -ARROW_LENGTH);
        glVertex3f( 0.0f,       -ARROW_SIZE, -ARROW_LENGTH);
        glVertex3f( 0.0f,       -ARROW_SIZE,  0.0f        );
        glVertex3f( ARROW_SIZE,  0.0f,        0.0f        );
        
        /* 
         * \
         */
        glVertex3f(-ARROW_SIZE,  0.0f,       -ARROW_LENGTH);
        glVertex3f( 0.0f,       -ARROW_SIZE, -ARROW_LENGTH);
        glVertex3f( 0.0f,       -ARROW_SIZE,  0.0f        );
        glVertex3f(-ARROW_SIZE,  0.0f,        0.0f        );
        
        /* /
         * 
         */
        glVertex3f(-ARROW_SIZE,  0.0f,       -ARROW_LENGTH);
        glVertex3f( 0.0f,        ARROW_SIZE, -ARROW_LENGTH);
        glVertex3f( 0.0f,        ARROW_SIZE,  0.0f        );
        glVertex3f(-ARROW_SIZE,  0.0f,        0.0f        );
        
        // Front cap
        glVertex3f( 0.0f,        ARROW_SIZE,  0.0f        );
        glVertex3f( ARROW_SIZE,  0.0f      ,  0.0f        );
        glVertex3f( 0.0f,        -ARROW_SIZE, 0.0f        );
        glVertex3f(-ARROW_SIZE,  0.0f,        0.0f        );
        
        // Bottom cap
        // Disabled due uselessness
        //~ glVertex3f( 0.0f,        ARROW_SIZE, -ARROW_LENGTH);
        //~ glVertex3f( ARROW_SIZE,  0.0f      , -ARROW_LENGTH);
        //~ glVertex3f( 0.0f,        -ARROW_SIZE,-ARROW_LENGTH);
        //~ glVertex3f(-ARROW_SIZE,  0.0f,       -ARROW_LENGTH);
         
    glEnd();
    
    // Arrowhead
    /*   /\
     *  /  \
     * /____\
     * 
     */
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLES);
        /*   /|
         *  / |
         * /__|
         * (upper)
         */
        glVertex3f( 0.0f,          0.0f,         ARROWHEAD_Z);
        glVertex3f( ARROWHEAD_XS,  0.0f,         0.0f);
        glVertex3f( 0.0f,          ARROWHEAD_YS, 0.0f);
        
        /*   /|
         *  / |
         * /__|
         * (lower)
         */
        glVertex3f( 0.0f,          0.0f,         ARROWHEAD_Z);
        glVertex3f( ARROWHEAD_XS,  0.0f,         0.0f);
        glVertex3f( 0.0f,         -ARROWHEAD_YS, 0.0f);
        
        /*    |\
         *    | \
         *    |__\
         * (upper)
         */
        glVertex3f( 0.0f,          0.0f,         ARROWHEAD_Z);
        glVertex3f(-ARROWHEAD_XS,  0.0f,         0.0f);
        glVertex3f( 0.0f,          ARROWHEAD_YS, 0.0f);
        
        /*    |\
         *    | \
         *    |__\
         * (lower)
         */
        glVertex3f( 0.0f,          0.0f,         ARROWHEAD_Z);
        glVertex3f(-ARROWHEAD_XS,  0.0f,         0.0f);
        glVertex3f( 0.0f,         -ARROWHEAD_YS, 0.0f);
        
        // Cap
        glVertex3f( 0.0f,         ARROWHEAD_YS,  0.0f        );
        glVertex3f( ARROWHEAD_XS, 0.0f,          0.0f        );
        glVertex3f( 0.0f,        -ARROWHEAD_YS,  0.0f        );
        glVertex3f(-ARROWHEAD_XS, 0.0f,          0.0f        );
    glEnd();
    
    glPopMatrix();
}

