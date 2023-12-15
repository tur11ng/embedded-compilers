#include <stdio.h>
#include <cblas.h>
#include <x86intrin.h>
#include <stdlib.h>

#include "exercise.h"
#include "../utils/utils.h"

#define EMBEDDED_COMPILERS_TILE_SIZE 16

void sgemm_loop_tiling(float *A, float *B, float *C) {
    for (int i = 0; i < EMBEDDED_COMPILERS_N; i += EMBEDDED_COMPILERS_TILE_SIZE) {
        for (int j = 0; j < EMBEDDED_COMPILERS_N; j += EMBEDDED_COMPILERS_TILE_SIZE) {
            for (int p = 0; p < EMBEDDED_COMPILERS_N; p += EMBEDDED_COMPILERS_TILE_SIZE) {
                // Compute matrix multiplication for the current tile
                for (int ii = i; ii < i + EMBEDDED_COMPILERS_TILE_SIZE && ii < EMBEDDED_COMPILERS_N; ++ii) {
                    for (int jj = j; jj < j + EMBEDDED_COMPILERS_TILE_SIZE && jj < EMBEDDED_COMPILERS_N; ++jj) {
                        for (int pp = p; pp < p + EMBEDDED_COMPILERS_TILE_SIZE && pp < EMBEDDED_COMPILERS_N; ++pp) {
                            C[ii * EMBEDDED_COMPILERS_N + jj] += A[ii * EMBEDDED_COMPILERS_N + pp] * B[pp * EMBEDDED_COMPILERS_N + jj];
                        }
                    }
                }
            }
        }
    }
}

void sgemm_loop_unrolling_simd(float *A, float *B, float *C) {
    // Assuming square matrices for simplicity
    const int n = EMBEDDED_COMPILERS_N;

    // Loop over blocks of the result matrix C
    for (int i = 0; i < n; i += 8) {
        for (int j = 0; j < n; j += 8) {
            // Use 2D array of AVX vectors to store the intermediate result
            __m256 c[8][8];
            // Load the current block of C into the 2D array
            for (int k = 0; k < 8; ++k) {
                for (int l = 0; l < 8; ++l) {
                    c[k][l] = _mm256_loadu_ps(&C[(i + k) * n + (j + l)]);
                }
            }

            // Perform matrix multiplication on the current block
            for (int k = 0; k < n; k += 8) {
                for (int kk = 0; kk < 8; ++kk) {
                    for (int ll = 0; ll < 8; ++ll) {
                        // Broadcast the B element to a vector
                        __m256 b = _mm256_broadcast_ss(&B[(j + ll) * n + (k + kk)]);
                        // Perform vectorized multiplication and addition
                        for (int i = 0; i < 8; ++i) {
                            // Load the A element to a vector
                            __m256 a = _mm256_loadu_ps(&A[(k + kk) * n + (i + i)]);
                            // Multiply A and B vectors and add to the intermediate result
                            c[i][ll] = _mm256_add_ps(c[i][ll], _mm256_mul_ps(a, b));
                        }
                    }
                }
            }

            // Store the intermediate result back to the result matrix C
            for (int k = 0; k < 8; ++k) {
                for (int l = 0; l < 8; ++l) {
                    _mm256_storeu_ps(&C[(i + k) * n + (j + l)], c[k][l]);
                }
            }
        }
    }
}

void sgemm_blas(float *A, float *B, float* C) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, EMBEDDED_COMPILERS_N, EMBEDDED_COMPILERS_N, EMBEDDED_COMPILERS_N, 1, A, EMBEDDED_COMPILERS_N, B, EMBEDDED_COMPILERS_N, 1, C, EMBEDDED_COMPILERS_N);
}


int main() {
    float A[EMBEDDED_COMPILERS_N * EMBEDDED_COMPILERS_N] = {0};
    float B[EMBEDDED_COMPILERS_N * EMBEDDED_COMPILERS_N] = {0};
    float C[EMBEDDED_COMPILERS_N * EMBEDDED_COMPILERS_N] = {0};

    float D[EMBEDDED_COMPILERS_N * EMBEDDED_COMPILERS_N] = {0};

    fill_array(A);
    fill_array(B);
    fill_array(C);

    PAPI_INIT();

    PAPI_MEASURE_START("sgemm_loop_tiling");
    sgemm_loop_tiling(A, B, C);
    PAPI_MEASURE_END("sgemm_loop_tiling");

    PAPI_MEASURE_START("sgemm_loop_unrolling_simd");
    sgemm_loop_unrolling_simd(A, B, C);
    PAPI_MEASURE_END("sgemm_loop_unrolling_simd");

    PAPI_MEASURE_START("sgemm_blas");
    sgemm_blas(A, B, C);
    PAPI_MEASURE_END("sgemm_blas");
}