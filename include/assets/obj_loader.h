#ifndef _OBJ_LOADER_H
#define _OBJ_LOADER_H

// OBJ file loader
#define SCAN_VERTICES 10
#define SCAN_VERTICES_STRING "%d %d %d %d %d %d %d %d %d %d"
#define SCAN_VERTICES_ARRAY_ITEMS_PTR(arr) &arr[0], &arr[1], &arr[2], &arr[3], &arr[4], &arr[5], &arr[6], &arr[7], &arr[8], &arr[9]

model_t *loadObj(const char* );

#endif
