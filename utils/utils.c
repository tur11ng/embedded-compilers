#include <assert.h>
#include <string.h>

#include "utils.h"

void fill_array(float array[]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array[i * N + j] = (float)rand() / (float)RAND_MAX;
        }
    }
}

void assert_array_equals(float* arr1, float* arr2, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        assert(arr1[i] == arr2[i]);
    }
}

void copy_array(const float* src, float* dest, size_t size) {
    memcpy(dest, src, size);
}

void gemm(float *A, float *B, float *C, size_t size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < size; ++k) {
                sum += A[i * size + k] * B[k * size + j];
            }
            C[i * size + j] = sum;
        }
    }
}