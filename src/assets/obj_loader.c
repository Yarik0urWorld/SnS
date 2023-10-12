// Undone
#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "all.h"

model_t *loadObj(const char *filename) {
	ssize_t read;
	size_t len = 0;
	char *line = NULL;
	char *comment_sym = NULL;
    float x = NAN, y = NAN, z = NAN;
    int scan_vertices_array[SCAN_VERTICES];
    size_t vertices_scanned, vcnt = 0, fcnt = 0;
    uint32_t v_count = 0, vt_count = 0, f_count = 0;
    uint32_t errors = 0;
    
    vertex_t *vertices;
    glprimitive_t *glps;
	model_t *r;
    
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
    
    if (f_count > 0) {
        glps = (glprimitive_t *)malloc(v_count * sizeof(glprimitive_t));
    } else {
        printf("Error: There must be 1 or more face.\n");
        return r;
    }
    
    r = (model_t *)malloc(sizeof(model_t));
    
    for (size_t i = 0; i < SCAN_VERTICES; i++) {
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
                        (vertices + vcnt)->x = x;
                        (vertices + vcnt)->y = y;
                        (vertices + vcnt)->z = z;
                        vcnt++;
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
                sscanf(line + 2, SCAN_VERTICES_STRING, SCAN_VERTICES_ARRAY_ITEMS_PTR(scan_vertices_array));
                for (vertices_scanned = 0; vertices_scanned < SCAN_VERTICES; vertices_scanned++) {
                    if (scan_vertices_array[vertices_scanned] == -1) break;
                }
                printf("%lu vertices: ", vertices_scanned);
                for (int i = 0; i < vertices_scanned; i++) {
                    printf("%d ", scan_vertices_array[i]);
                }
                printf("\n");
                (glps + fcnt)->vertex_count = vertices_scanned;
                (glps + fcnt)->vertices = (vertex_t *)malloc(vertices_scanned * sizeof(vertex_t));
                (glps + fcnt)->type = GL_POLYGON;
                for (int i = 0; i < vertices_scanned; i++) {
                    *((glps + fcnt)->vertices + i) = *(vertices + scan_vertices_array[i] - 1);
                }
                fcnt++;
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
	
    free(vertices);
    r->glp_count = f_count;
    r->glps = glps;
    
    if (errors) {
        printf("Found %d errors in scanned file!", errors);
    }
    
	return r;
}


//~ // Main here is for testing
//~ int main() {
	//~ loadObj("sample.obj");
//~ }
