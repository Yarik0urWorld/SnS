#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

#include "defs.h"

FILE *openModelFile(const char *fname);
void closeModelFile(FILE *f);
void writeInit(FILE *f);
void writeFunc(FILE *f, const char *fname);
void endFunc(FILE *f);
void writeTriangle(FILE *f, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
void writeQuad(FILE *f, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
void writePushMatrix(FILE *f);
void writePopMatrix(FILE *f);
void writeTranslate(FILE *f, float x, float y, float z);
void writeColor(FILE *f, float r, float g, float b);
void writeSphere(FILE *f, float radius, int slices, int stacks);
void writeCylinder(FILE *f, float base, float top, float height, uint16_t slices);


FILE *openModelFile(const char *fname) {
	FILE *f = fopen(fname, "w");
	if (f == NULL) {
		perror("fopen");
		exit(1);
	}
	writeInit(f);
	return f;
}

// For close handling (in furture?)
void closeModelFile(FILE *f) {
	fclose(f);
}

void writeInit(FILE *f) {
    // dosn' work
	//fprintf(f, "// Machine generated file\n#include <GL/gl.h>\n\nvoid t(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {\n\tglBegin(GL_TRIANGLES);\n\t\tglVertex3f(x1, y1, z1);\n\t\tglVertex3f(x2, y2, z2);\n\t\tglVertex3f(x3, y3, z3);\n\tglEnd();\n}\n\nvoid q(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4) {\n\tglBegin(GL_QUADS);\n\t\tglVertex3f(x1, y1, z1);\n\t\tglVertex3f(x2, y2, z2);\n\t\tglVertex3f(x3, y3, z3);\n\t\tglVertex3f(x4, y4, z4);\n\tglEnd();\n}\n\n");
    fprintf(f, "// Machine generated file\n#include <GL/gl.h>\n");
}

void writeFunc(FILE *f, const char *fname) {
	fprintf(f, "void %s() {\n", fname);
}

void endFunc(FILE *f) {
	fprintf(f, "}\n\n");
}

void writeTriangle(FILE *f, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
	fprintf(f, "\tt(%f,%f,%f,%f,%f,%f,%f,%f,%f);\n", x1, y1, z1, x2, y2, z2, x3, y3, z3);
}

void writeQuad(FILE *f, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4) {
	fprintf(f, "\tq(%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f);\n", x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
}

void writePushMatrix(FILE *f) {
	fprintf(f, "\tglPushMatrix();\n");
}

void writePopMatrix(FILE *f) {
	fprintf(f, "\tglPopMatrix();\n");
}

void writeTranslate(FILE *f, float x, float y, float z) {
	fprintf(f, "\tglTranslatef(%f, %f, %f);\n", x, y, z);
}

void writeColor(FILE *f, float r, float g, float b) {
    fprintf(f, "\tglColor3f(%f, %f, %f);\n", r, g, b);
}

void writeBegin(FILE *f, const char *type) {
    fprintf(f, "\tglBegin(%s);\n", type);
}

void endBegin(FILE *f) {
    fprintf(f, "\tglEnd();\n");
}

void writeVertex(FILE *f, float x, float y, float z) {
    fprintf(f, "\t\tglVertex3f(%f, %f, %f);\n", x, y, z);
}

// Thanks http://www.cburch.com/cs/490/sched/feb8/
// Carl Burch is a good person ;)
void writeSphere(FILE *f, float r, int lats, int longs) {
    int i, j;
    for(i = 0; i <= lats; i++) {
        float lat0 = M_PI * (-0.5 + (float) (i - 1) / lats);
        float z0  = sin(lat0);
        float zr0 =  cos(lat0);
    
        float lat1 = M_PI * (-0.5 + (float) i / lats);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);
    
        writeBegin(f, "GL_QUAD_STRIP");
        for(j = 0; j <= longs; j++) {
            float lng = 2 * M_PI * (float) (j - 1) / longs;
            float x = cos(lng);
            float y = sin(lng);

            //~ glNormal3f(x * zr0, y * zr0, z0);
            //~ glVertex3f(x * zr0, y * zr0, z0);
            //~ glNormal3f(x * zr1, y * zr1, z1);
            //~ glVertex3f(x * zr1, y * zr1, z1);
            writeVertex(f, x * zr0 * r, y * zr0 * r, z0 * r);
            writeVertex(f, x * zr1 * r, y * zr1 * r, z1 * r);
        }
        endBegin(f);
    }
}

// Thanks https://stackoverflow.com/questions/31670939/techniques-to-draw-a-solid-transparent-cone
// first time when the question itself (not the answers) helps
void writeCylinder(FILE *f, float bottom, float top, float height, uint16_t slices) {
    float increment = 360.0f / slices;
    writeBegin(f, "GL_TRIANGLE_STRIP");
    for (float ang = 0; ang <= 360; ang += increment)
    {
        writeVertex(f, bottom*cos((ang*M_PI)/180), bottom*sin((ang*M_PI)/180), 0.0f);
        writeVertex(f, top*cos((ang*M_PI)/180), top*sin((ang*M_PI)/180), height);
    }
    endBegin(f);
}

int main() {
	FILE *f = openModelFile("../build/snowman.mdl.c");
    int quality = 1;
    
    writeFunc(f, "mdl_snowmanBody");
    
    // Smowman's body
    writeColor(f, 1.0f, 1.0f, 1.0f);
	writeTranslate(f, 0.0f, 0.75f, 0.0f);
	writeSphere(f, 0.75, (quality + 1) * 10, (quality + 1) * 10);
 	
    endFunc(f);
    
    writeFunc(f, "mdl_snowmanHead");
    
    // Snowman's head
    writeSphere(f, 0.25, (quality + 1) * 7, (quality + 1) * 7);
	
    // Snowman's eyes
	writePushMatrix(f);
	writeColor(f, 0.0f, 0.0f, 0.0f);
	writeTranslate(f, 0.05f, 0.10f, 0.18f);
	writeSphere(f, 0.05f, (quality + 1) * 4, (quality + 1) * 4);
	writeTranslate(f, -0.1f, 0.0f, 0.0f);
	writeSphere(f, 0.05f, (quality + 1) * 4, (quality + 1) * 4);
	writePopMatrix(f);
    
	// Snowman's nose
	writeColor(f, 1.0f, 0.5f , 0.5f);
	writeCylinder(f, 0.08f, 0.0f, 0.5f, quality * 5);
    
    endFunc(f);
    
    closeModelFile(f);
    
    f = openModelFile("../build/gas.mdl.c");
    
    writeFunc(f, "mdl_gas");
    
    writeColor(f, 0.75f, 0.85f, 0.25f);
    writeSphere(f, ENEMY_RADIUS, 10, 10);
    
    endFunc(f);
    
    closeModelFile(f);
}
