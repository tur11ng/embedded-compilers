#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cblas.h>

#include "../utils/utils.h"

#ifndef N
#error "N must be defined"
#endif

#ifndef BLOCK_SIZE
#error "BLOCK_SIZE must be defined"
#endi

#ifndef L1_CACHE_LINE_SIZE // Or sysconf (_SC_LEVEL1_DCACHE_LINESIZE)
#error "L1_CACHE_LINE_SIZE must be defined"
#endi

f#define L1_CACHE_LINE_SIZE 64

void sgemm_dummy(float *A, float *B, float *C) {
    for (int k=0; k<N; k++) {
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

void sgemm_loop_tiling() {
    for (int k=0; k<N; k+=BLOCK_SIZE) {
        for (int i=0; i<N; i+=BLOCK_SIZE) {
            for (int j=0; j<N; j+=BLOCK_SIZE) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

void sgemm_loop_unrolling_simd() {

}

void sgemm_blas(float *A, float *B, float* C) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, A, 0, B, 0, 1, C, 0);
}

int main() {
    srand(time(NULL));

    float A[N * N];
    float B[N * N];
    float C[N * N];

    fill_array(A);
    fill_array(B);
    fill_array(C);
}