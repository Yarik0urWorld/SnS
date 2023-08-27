#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
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
