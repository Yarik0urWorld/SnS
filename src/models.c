#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <stdarg.h>
#include "all.h"

model_t *models[MODEL_COUNT];
char *model_names[MODEL_COUNT];
size_t models_loaded = 0;

model_t *loadModelFromAssets(const char *name) {
	if (endsWith(name, ".obj")) {
		return loadObj(name);
	} else {
		fprintf(stderr, "[Error] Unable to load model \"%s\": unknown format\n", name);
		return NULL;
	}
}

// Return value: -1 if error, model id if success
int loadModel(const char *name) {
	model_t *model = loadModelFromAssets(name);
	if (model == NULL) return -1;
	if (models_loaded >= MODEL_COUNT) fprintf(stderr, "[Error] Unable to load model \"%s\": limit exeeded (programmer's stupid)\n", name);
	
	models[models_loaded] = model;
	model_names[models_loaded] = (char *)malloc(BUF_SZ);
	strcpy(model_names[models_loaded], name);
	return models_loaded++;
}

void drawGLPrimitive(const glprimitive_t *glp) {
	glColor3f(glp->color.r, glp->color.g, glp->color.b);
	
	glBegin(glp->type);
	for (int vertex = 0; vertex < glp->vertex_count; vertex++) {
		glVertex3f(
			(glp->vertices + vertex)->x,
			(glp->vertices + vertex)->y,
			(glp->vertices + vertex)->z
		);
	}
	glEnd();
} 

void drawModel(const model_t *model) {
	for (size_t glp = 0; glp < model->glp_count; glp++) {
		drawGLPrimitive(model->glps+glp);
	}
}


void deleteGLPrimitiveFast(const glprimitive_t *glp) {
	free(glp->vertices);
}

void deleteGLPrimitive(glprimitive_t *glp) {
	free(glp->vertices);
	glp->vertex_count = 0;
}

void deleteModel(model_t *model) {
	for (size_t glp = 0; glp < model->glp_count; glp++) {
		deleteGLPrimitiveFast(model->glps+glp);
	}
	free(model->glps);
	model->glp_count = 0;
}

void translateModel(model_t *model, vertex_t translate_vertex) {
	size_t glp, vertex;
	glprimitive_t *current;
	
	for (glp = 0; glp < model->glp_count; glp++) {
		current = (model->glps + glp);
		for (vertex = 0; vertex < current->vertex_count; vertex++) {
			(current->vertices + vertex)->x += translate_vertex.x;
			(current->vertices + vertex)->y += translate_vertex.y;
			(current->vertices + vertex)->z += translate_vertex.z;
		}
	}
}

model_t *joinModels(_Bool del, int num, ...) {
	model_t **separated = (model_t **)malloc(sizeof(model_t *) * num);
	model_t *joined = (model_t *)malloc(sizeof(model_t));
	model_t *model;
	glprimitive_t *total_glps;
	size_t total_glp_count = 0, total_i = 0, curr_model, curr_glp;
	va_list valist;
	
	va_start(valist, num);
	for (int i = 0; i < num; i++) {
		*(separated + i) = va_arg(valist, model_t *);
		total_glp_count += (*(separated + i))->glp_count;
	}
	va_end(valist);
	
	total_glps = (glprimitive_t *)malloc(sizeof(glprimitive_t) * total_glp_count);
	for (curr_model = 0; curr_model < num; curr_model++) {
		model = *(separated + curr_model);
		for (curr_glp = 0; curr_glp < model->glp_count; curr_glp++) {
			//~ *(total_glps + total_i) = *(model->glps + curr_glp);
			memcpy((void *)(total_glps + total_i), (void *)(model->glps + curr_glp), sizeof(glprimitive_t));
			total_i++;
		}
		if (del) deleteModel(model);
	}
	
	joined->glp_count = total_glp_count;
	joined->glps = total_glps;
	
	free(separated);
	return joined;
}

model_t *createSphere(float r, int lats, int longs, color_t color) {
	model_t *model = (model_t *)malloc(sizeof(model_t));
	vertex_t *v;
	
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
		
		v = (model->glps + i)->vertices;
        for(j = 0; j <= longs; j++) {
            float lng = 2 * M_PI * (float) (j - 1) / longs;
            float x = cos(lng);
            float y = sin(lng);

            //~ glNormal3f(x * zr0, y * zr0, z0);
            //~ glVertex3f(x * zr0, y * zr0, z0);
            //~ glNormal3f(x * zr1, y * zr1, z1);
            //~ glVertex3f(x * zr1, y * zr1, z1);
            v->x = x * zr0 * r;
            v->y = y * zr0 * r;
            (v++)->z = z0 * r;
            v->x = x * zr1 * r;
            v->y = y * zr1 * r;
            (v++)->z = z1 * r;
        }
    }
    return model;
}

model_t *createCylinder(float bottom, float top, float height, S_uint32_t slices, color_t color) {
	model_t *model = (model_t *)malloc(sizeof(model_t));
	glprimitive_t *glp = (glprimitive_t *)malloc(sizeof(glprimitive_t));
	vertex_t *v;
	
    float increment = 360.0f / slices;
    float ang = 0.0;

	model->glp_count = 1;
	model->glps = glp;
	
	glp->type = GL_TRIANGLE_STRIP;
	glp->vertex_count = (slices + 1) * 2;
	glp->vertices = (vertex_t *)malloc(sizeof(vertex_t) * glp->vertex_count);
	glp->color = color;
	
	v = glp->vertices;
    for (S_uint32_t i = 0; i < glp->vertex_count; i++) {
		v = glp->vertices + i;
        v->x = bottom*cos((ang*M_PI)/180);
        v->y = bottom*sin((ang*M_PI)/180);
        (v++)->z = 0.0f;
        i++;
        v->x = top*cos((ang*M_PI)/180);
        v->y = top*sin((ang*M_PI)/180);
        (v++)->z = height;
        ang += increment;
    }
    
    return model;
}

//FIXME
void createModels() {
	model_t *snowman_body, *snowman_head, *gas, *head, *eye1, *eye2, *nose;
	vertex_t v;
	color_t c;
   
    // Smowman's body
    c.r = c.g = c.b = 1.0f;
    v.x = v.z = 0.0f;
    v.y = 0.75f;
	snowman_body = createSphere(0.75, (quality + 1) * 10, (quality + 1) * 10, c);
	translateModel(snowman_body, v);
    
    // Snowman's head
    c.r = c.g = c.b = 1.0f;
    head = createSphere(0.25, (quality + 1) * 7, (quality + 1) * 7, c);
	
    // Snowman's eyes
    v.x = 0.05f;
    v.y = 0.10f;
    v.z = 0.18f;
    c.r = c.g = c.b = 0.0f;
	eye1 = createSphere(0.05f, (quality + 1) * 4, (quality + 1) * 4, c);
	translateModel(eye1, v);
	
	v.x -= 0.1f;
	eye2 = createSphere(.05f, (quality + 1) * 4, (quality + 1) * 4, c);
	translateModel(eye2, v);
	
	// Snowman's nose
	c.r = 1.0f;
	c.g = c.b = 0.5f;
	nose = createCylinder(0.08f, 0.0f, 0.5f, quality * 5, c);
	translateModel(nose, v); 
    
    // Snowman's completed head
    snowman_head = joinModels(0, 4, head, eye1, eye2, nose);
    //~ snowman_head = head; // ignore my memory leak (FIXME)

    // Gas
    c.r = 0.75f;
    c.g = 0.85f;
    c.b = 0.25f;
    gas = createSphere(ENEMY_RADIUS, 10, 10, c);
    
	models[0] = snowman_body;
	models[1] = snowman_head;
	models[2] = gas;
}
