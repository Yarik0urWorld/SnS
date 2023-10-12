#ifndef _MODELS_H
#define _MODELS_H

// Model management

model_t *loadModelFromAssets(const char *);

// Return value: -1 if error, model id if success
int loadModel(const char *);

void drawGLPrimitive(const glprimitive_t *);
void drawModel(const model_t *);

void deleteGLPrimitiveFast(const glprimitive_t *);
void deleteGLPrimitive(glprimitive_t *);
void deleteModel(model_t *);

void translateModel(model_t *, vertex_t);
model_t *joinModels(_Bool, int, ...);

model_t *createSphere(float, int, int, color_t);
model_t *createCylinder(float, float, float, S_uint32_t, color_t);

void createModels();
#endif
