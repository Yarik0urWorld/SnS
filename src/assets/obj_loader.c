// Undone
#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

//~ #include "vars.h"
#define PACK

#define SCAN_VERICES 10
#define SCAN_VERICES_STRING "%d %d %d %d %d %d %d %d %d %d"
#define SCAN_VERICES_ARRAY_ITEMS(arr) arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9]

typedef struct PACK _vertex {
	float x, y, z;
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
    float x = NAN, y = NAN, z = NAN;
    int scan_vertices_array[SCAN_VERICES];
    size_t vertices_scanned;
    uint32_t v_count = 0, vt_count = 0, f_count = 0;
    uint32_t errors = 0;
    
    vertex_t *vertices;
    face_t *faces;
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
    
    for (size_t i = 0; i < SCAN_VERICES; i++) {
        scan_vertices_array[i] = -1;
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
                        errors++;
                        break;
                    default:
                        printf("Other vertice (ignore it)\n");
                }
                break;
            case 'f':
                printf("Face\n");
                sscanf(line + 2, SCAN_VERICES_STRING, SCAN_VERICES_ARRAY_ITEMS(scan_vertices_array));
                for (vertices_scanned = 0; vertices_scanned < SCAN_VERICES; vertices_scanned++) {
                    if (scan_vertices_array[vertices_scanned] == -1) break;
                }
                
                break;
            case '\0':
            case ' ':
            case '\n':
            case '#':
                printf("Empty line\n");
                break;
            default:
                printf("ERROR! Something unsupported\n");
                errors++;
		}
        printf("\n");
	}
	fflush(stdout);
	
    if (errors) {
        printf("Found %d errors in scanned file!", errors);
    }
    
	return r; // for now
}


// Main here is for testing
int main() {
	loadObj("sample.obj");
}
