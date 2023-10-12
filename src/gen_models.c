#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

#include "defs.h"
#include "vars.h"

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

// For close handling (in future?)
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
// Carl Burch is a good person ;) Logisim 1love
void writeSphere(FILE *f, float r, int lats, int longs) {
    int i, j;
    for(i = 0; i <= lats; i++) {
        float lat0 = M_PI * (-0.5 + (float) (i - 1) / lats);
        float z0  = sin(lat0);
        float zr0 =  cos(lat0);
    
        float lat1 = M_PI * (-0.5 + (float) i / lats);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);
    
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
    }
}
/*
model_t *createSphere(float r, int lats, int longs, color_t color) {
	model_t *model = (model_t *)malloc(sizeof(model_t));
	
	model->glp_count = lats;
	model->glps = (glprimitive_t *)malloc(sizeof(glprimitive_t) * (lats + 1));
	
    int i, j;
    for(i = 0; i <= lats; i++) {
        float lat0 = M_PI * (-0.5 + (float) (i - 1) / lats);
        float z0  = sin(lat0);
        float zr0 =  cos(lat0);
    
        float lat1 = M_PI * (-0.5 + (float) i / lats);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);
		
		// initialize glprimitive
		(model->glps + i)->type = GL_QUAD_STRIP;
		(model->glps + i)->vertex_count = (longs + 1) * 2;
		(model->glps + i)->vertices = (vertex_t *)malloc(sizeof(vertex_t) * (model->glps + i)->vertex_count);
		(model->glps + i)->color = color;
		
        for(j = 0; j <= longs; j++) {
            float lng = 2 * M_PI * (float) (j - 1) / longs;
            float x = cos(lng);
            float y = sin(lng);

            //~ glNormal3f(x * zr0, y * zr0, z0);
            //~ glVertex3f(x * zr0, y * zr0, z0);
            //~ glNormal3f(x * zr1, y * zr1, z1);
            //~ glVertex3f(x * zr1, y * zr1, z1);
            *((model->glps + i)->vertices + j*2) = {x * zr0 * r, y * zr0 * r, z0 * r};
            *((model->glps + i)->vertices + j*2 + 1) = {x * zr1 * r, y * zr1 * r, z1 * r};
        }
    }
}

// Thanks https://stackoverflow.com/questions/31670939/techniques-to-draw-a-solid-transparent-cone
// first time when the question itself (not the answers) helps
void writeCylinder(FILE *f, float bottom, float top, float height, S_uint32_t slices) {
    float increment = 360.0f / slices;
    float ang = 0.0;
	S_uint32_t vertice_pairs = slices + 1;
    writeBegin(f, "GL_TRIANGLE_STRIP");
    for (S_uint32_t i; i < vetrice_pairs; i++) {
        writeVertex(f, bottom*cos((ang*M_PI)/180), bottom*sin((ang*M_PI)/180), 0.0f);
        writeVertex(f, top*cos((ang*M_PI)/180), top*sin((ang*M_PI)/180), height);
        ang += increment
    }
    endBegin(f);
}

model_t *createCylinder(float bottom, float top, float height, S_uint32_t slices, color_t color) {
	model_t *model = (model_t *)malloc(sizeof(model_t));
	glprimitive_t *glp = (glprimitive_t *)malloc(sizeof(glprimitive_t));
	
    float increment = 360.0f / slices;
    float ang = 0.0;

	model->glp_count = 1;
	model->glps = glp;
	
	glp->type = GL_TRIANGLE_STRIP;
	glp->vertex_count = (slices + 1) * 2;
	glp->vertices = (vertex_t *)malloc(sizeof(vertex_t) * glp->vertex_count);
	glp->color = color;
	
    for (S_uint32_t i; i < glp->vertex_count; i++) {
        *(glp->vertices + i) = {bottom*cos((ang*M_PI)/180), bottom*sin((ang*M_PI)/180), 0.0f};
        *(glp->vertices + ++i) = {top*cos((ang*M_PI)/180), top*sin((ang*M_PI)/180), height};
        ang += increment;
    }
    
    return model;
}
*/

int main(){} //FIXME
/*
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
*/
