#include <GL/gl.h>

#include "all.h"

float gunReload = 0.0f;

void drawGun() {
    glPushMatrix();
    
    computeDir(GUN_ROT);
    glTranslatef(x + lx, EYE_Y - 0.3f, z + lz);
    computeDir(-GUN_ROT);
    glRotatef(180.0f - RADTODEG(angle), 0.0f, 1.0f, 0.0f);
    glRotatef(85.0f, 0.0f, 0.0f, -1.0f);

   
    //~ glutSolidCone(0.15f, 0.5f, 30, 2);
    
    /*        ________
     *  _____/ __o___ \______ 
     * |______/------\_______|
     */
    
    /*        
     *  
     *         ------
     */


    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f( BOWBODY_CURVE_LN,  BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET                                                      );
        glVertex3f( 0.0f            ,  BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET - BOWSPRING_MAX_TENSION * (gunReload / GUNRELOAD_MAX));
        glVertex3f( 0.0f            ,  BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET - BOWSPRING_MAX_TENSION * (gunReload / GUNRELOAD_MAX));
        glVertex3f(-BOWBODY_CURVE_LN,  BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET                                                      );
    glEnd();

    glColor3f(0.58f, 0.32f, 0.0f);

    // Very hard...
    glBegin(GL_QUADS);
        
        // -----------------------
        //        UPPER PART
        // -----------------------        
    
        /*        ________
         *        ________ 
         * (upper)
         */
    
        glVertex3f( BOWBODY_FRONT_LN,  BOW_THICKNESS,  BOW_THICKNESS);
        glVertex3f(-BOWBODY_FRONT_LN,  BOW_THICKNESS,  BOW_THICKNESS);
        glVertex3f(-BOWBODY_FRONT_LN,  BOW_THICKNESS, -BOW_THICKNESS);
        glVertex3f( BOWBODY_FRONT_LN,  BOW_THICKNESS, -BOW_THICKNESS);
        
        /*
         *               ________ 
         *               \_______|
         * (upper)
         */
    
        glVertex3f( BOWBODY_FRONT_LN,  BOW_THICKNESS,  BOW_THICKNESS                       );
        glVertex3f( BOWBODY_CURVE_LN,  BOW_THICKNESS,  BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f( BOWBODY_CURVE_LN,  BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f( BOWBODY_FRONT_LN,  BOW_THICKNESS, -BOW_THICKNESS                       );
        
        /*  
         *  _______ 
         * |______/
         * (upper)
         */
        
        glVertex3f(-BOWBODY_FRONT_LN,  BOW_THICKNESS,  BOW_THICKNESS                       );
        glVertex3f(-BOWBODY_CURVE_LN,  BOW_THICKNESS,  BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f(-BOWBODY_CURVE_LN,  BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f(-BOWBODY_FRONT_LN,  BOW_THICKNESS, -BOW_THICKNESS                       );
        
        // -----------------------
        //        LOWER PART
        // -----------------------  
        
        glVertex3f(-BOWBODY_FRONT_LN, -BOW_THICKNESS,  BOW_THICKNESS                       );
        glVertex3f(-BOWBODY_CURVE_LN, -BOW_THICKNESS,  BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f(-BOWBODY_CURVE_LN, -BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f(-BOWBODY_FRONT_LN, -BOW_THICKNESS, -BOW_THICKNESS                       );
        
        /*        ________
         *        ________ 
         * (lower)
         */
    
        glVertex3f( BOWBODY_FRONT_LN, -BOW_THICKNESS,  BOW_THICKNESS);
        glVertex3f(-BOWBODY_FRONT_LN, -BOW_THICKNESS,  BOW_THICKNESS);
        glVertex3f(-BOWBODY_FRONT_LN, -BOW_THICKNESS, -BOW_THICKNESS);
        glVertex3f( BOWBODY_FRONT_LN, -BOW_THICKNESS, -BOW_THICKNESS);
        
        /*
         *               ________ 
         *               \_______|
         * (lower)
         */
    
        glVertex3f( BOWBODY_FRONT_LN, -BOW_THICKNESS,  BOW_THICKNESS                       );
        glVertex3f( BOWBODY_CURVE_LN, -BOW_THICKNESS,  BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f( BOWBODY_CURVE_LN, -BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f( BOWBODY_FRONT_LN, -BOW_THICKNESS, -BOW_THICKNESS                       );
        
        /*  
         *  _______ 
         * |______/
         * (lower)
         */
         
        glVertex3f(-BOWBODY_FRONT_LN, -BOW_THICKNESS,  BOW_THICKNESS                       );
        glVertex3f(-BOWBODY_CURVE_LN, -BOW_THICKNESS,  BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f(-BOWBODY_CURVE_LN, -BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f(-BOWBODY_FRONT_LN, -BOW_THICKNESS, -BOW_THICKNESS                       );
        
        // -----------------------
        //        "WALLS"
        // -----------------------
        
        /*        
         *         ______
         * 
         */
        glVertex3f( BOWBODY_FRONT_LN,  BOW_THICKNESS, -BOW_THICKNESS);
        glVertex3f(-BOWBODY_FRONT_LN,  BOW_THICKNESS, -BOW_THICKNESS);
        glVertex3f(-BOWBODY_FRONT_LN, -BOW_THICKNESS, -BOW_THICKNESS);
        glVertex3f( BOWBODY_FRONT_LN, -BOW_THICKNESS, -BOW_THICKNESS);
        
        /*  
         *  
         *  ______
         */
        
        glVertex3f(-BOWBODY_FRONT_LN,  BOW_THICKNESS, -BOW_THICKNESS                       ); 
        glVertex3f(-BOWBODY_CURVE_LN,  BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f(-BOWBODY_CURVE_LN, -BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f(-BOWBODY_FRONT_LN, -BOW_THICKNESS, -BOW_THICKNESS                       ); 
        
        /*
         *
         *                _______
         */
         
        glVertex3f( BOWBODY_FRONT_LN,  BOW_THICKNESS, -BOW_THICKNESS                       ); 
        glVertex3f( BOWBODY_CURVE_LN,  BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f( BOWBODY_CURVE_LN, -BOW_THICKNESS, -BOW_THICKNESS - BOWBODY_CURVE_OFFSET);
        glVertex3f( BOWBODY_FRONT_LN, -BOW_THICKNESS, -BOW_THICKNESS                       ); 
    glEnd();
    
    glPopMatrix();
}

void gunLogic() {
    if (gunReload > 0.0f) {
        gunReload -= GUNRELOAD_MAX / GUNRELOAD_TIME * tpf;
        
        if (gunReload < 0.0f) gunReload = 0.0f; // oops, we did too much :o)
    }
}
