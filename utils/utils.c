#include "utils.h"

void fill_array(float array[]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array[i * N + j] = (float)rand() / (float)RAND_MAX;
        }
    }
}