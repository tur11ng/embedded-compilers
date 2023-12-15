#include <assert.h>
#include <string.h>

#include "utils.h"

void fill_array(float array[]) {
    for (int i = 0; i < EMBEDDED_COMPILERS_N; i++) {
        for (int j = 0; j < EMBEDDED_COMPILERS_N; j++) {
            array[i * EMBEDDED_COMPILERS_N + j] = (float)rand() / (float)RAND_MAX;
        }
    }
}