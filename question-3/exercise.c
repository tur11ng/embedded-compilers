#include <stdio.h>
#include <time.h>
#include <cblas.h>
#include <x86intrin.h>
#include <stdlib.h>

#include "exercise.h"
#include "../utils/utils.h"

//void sgemm_loop_tiling(float *A, float *B, float *C) {
//    float *tileA = (float *)malloc(GEMM_BLOCK_SIZE * GEMM_BLOCK_SIZE * sizeof(float));
//
//    for (int i = 0; i < N; i += GEMM_BLOCK_SIZE) {
//        for (int j = 0; j < N; j += GEMM_BLOCK_SIZE) {
//            for (int k = 0; k < K; k += GEMM_BLOCK_SIZE) {
//
//                for (int ii = 0; ii < GEMM_BLOCK_SIZE; ii++) {
//                    for (int kk = 0; kk < GEMM_BLOCK_SIZE; kk++) {
//                        tileA[ii * GEMM_BLOCK_SIZE + kk] = A[(i + ii) * K + (k + kk)];
//                    }
//                }
//
//                for (int jj = 0; jj < N; jj += GEMM_BLOCK_SIZE) {
//
//                    for (int ii = 0; ii < GEMM_BLOCK_SIZE; ii++) {
//                        for (int kk = 0; kk < GEMM_BLOCK_SIZE; kk++) {
//                            float sum = C[(i + ii) * N + (j + jj + kk)];
//                            for (int jjj = 0; jjj < GEMM_BLOCK_SIZE; jjj++) {
//                                sum += tileA[ii * GEMM_BLOCK_SIZE + jjj] * B[(k + kk) * N + (j + jj + jjj)];
//                            }
//                            C[(i + ii) * N + (j + jj + kk)] = sum;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    free(tileA);
//}

//void sgemm_loop_unrolling_simd(float *A, float *B, float *C) {
//    // Loop unrolling factors
//    const int unroll_m = 8;
//    const int unroll_n = 8;
//
//    // Iterate over the rows of A
//    for (int i = 0; i < N; i += unroll_m) {
//        // Iterate over the columns of B
//        for (int j = 0; j < N; j += unroll_n) {
//            // Initialize result vectors
//            __m256 result[unroll_m];
//
//            // Perform the multiplication and accumulate the results
//            for (int k = 0; k < K; k++) {
//                for (int ii = 0; ii < unroll_m; ++ii) {
//                    result[ii] = _mm256_fmadd_ps(
//                            _mm256_loadu_ps(&A[(i + ii) * K + k]),
//                            _mm256_broadcast_ss(&B[k * N + j]),
//                            result[ii]
//                    );
//                }
//            }
//
//            // Store the result vectors in the output matrix
//            for (int ii = 0; ii < unroll_m; ii++) {
//                _mm256_storeu_ps(&C[(i + ii) * N + j], result[ii]);
//            }
//        }
//    }
//}

void sgemm_blas(float *A, float *B, float* C) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, A, 0, B, 0, 1, C, 0);
}

int main() {
    float A[N * N] = {0};
    float B[N * N] = {0};
    float C[N * N] = {0};

    fill_array(A);
    fill_array(B);
    fill_array(C);

    PAPI_INIT();

    PAPI_MEASURE_START("ijk");
    sgemm_blas(A, B, C);
    PAPI_MEASURE_END("ijk");
}