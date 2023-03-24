// Undone
#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

//~ #include "vars.h"
#define PACK


typedef struct PACK _vertex {
	float x, y, z, u, v; // u and v can be NaN
} vertex_t;

typedef struct PACK _face {
	uint8_t count;
	vertex_t *vertices;
} face_t;

typedef struct PACK _model {
	uint8_t face_count;
	face_t *faces;
	//~ GLuint texture;
} model_t;

model_t loadObj(const char *filename) {
	ssize_t read;
	size_t len = 0;
	char *line = NULL;
	char *comment_sym = NULL;
    float x = NAN, y = NAN, z = NAN, u = NAN, v = NAN;
    uint32_t v_count = 0, vt_count = 0, f_count = 0;
    
    vertex_t *vertices;
	model_t r;
    
	FILE *f = fopen(filename, "r");
	
    while ((read = getline(&line, &len, f)) != -1) {
        switch (*line) {
            case 'v':
                switch (*(line + 1)) {
                    case ' ':
                        v_count++;
                        break;
                    case 't':
                        vt_count++;
                        break;
                }
                break;
            case 'f':
                f_count++;
                break;
		}
    }
    
    printf("Search report:\n\tVertices: %u\n\tTexture vertices: %u\n\tFaces: %u\n\n", v_count, vt_count, f_count);
    
    if (v_count > 0) {
        vertices = (vertex_t *)malloc(v_count * sizeof(vertex_t));
    } else {
        printf("Error: There must be 1 or more vertice.\n");
        return r;
    }
    
    if (v_count > 0) {
        vertices = (vertex_t *)malloc(v_count * sizeof(vertex_t));
    } else {
        printf("Error: There must be 1 or more vertice.\n");
        return r;
    }
    
    fseek(f, 0, SEEK_SET);
    
	while ((read = getline(&line, &len, f)) != -1) {
        comment_sym = strchr(line, '\n');
        if (comment_sym != NULL) *comment_sym = '\0';
        comment_sym = strchr(line, '#');
        if (comment_sym != NULL) *comment_sym = '\0';
        printf("Read line: %s\n", line);
        switch (*line) {
            case 'v':
                switch (*(line + 1)) {
                    case ' ':
                        printf("Basic vertice\n");
                        sscanf(line + 2, "%f %f %f", &x, &y, &z);
                        printf("Vertice x=%f y=%f z=%f\n", x, y, z);
                        break;
                    case 't':
                        printf("Texture vertice\n");
                        break;
                    case '\0':
                        printf("ERROR! Bad vertice!\n");
                        break;
                    default:
                        printf("Other vertice (ignore it)\n");
                }
                break;
            case 'f':
                printf("Face\n");
                break;
            case '\0':
            case ' ':
            case '\n':
            case '#':
                printf("Empty line\n");
                break;
            default:
                printf("Something unsupported\n");
		}
        printf("\n");
	}
	fflush(stdout);
	
	return r; // for now
}


// Main here is for testing
int main() {
	loadObj("sample.obj");
}
