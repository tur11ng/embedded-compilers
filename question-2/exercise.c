#include <stdio.h>
#include <stdlib.h>

#include "exercise.h"
#include "../utils/utils.h"

int main() {
    float A[N * N] = {0};
    float B[N * N] = {0};
    float C[N * N] = {0};

    float D[N * N] = {0};

    fill_array(A);
    fill_array(B);
    fill_array(C);

    gemm(A, B, C, N);
    copy_array(C, D, N);

    PAPI_INIT();

    PAPI_MEASURE_START("ijk");
    SGEMM(i, j, k);
    PAPI_MEASURE_END("ijk");
    assert_array_equals(C, D, N);

    PAPI_MEASURE_START("ikj");
    SGEMM(i, k, j);
    PAPI_MEASURE_END("ikj");
    assert_array_equals(C, D, N);

    PAPI_MEASURE_START("jik");
    SGEMM(j, i, k);
    PAPI_MEASURE_END("jik");
    assert_array_equals(C, D, N);

    PAPI_MEASURE_START("jki");
    SGEMM(j, k, i);
    PAPI_MEASURE_END("jki");
    assert_array_equals(C, D, N);

    PAPI_MEASURE_START("kij");
    SGEMM(k, i, j);
    PAPI_MEASURE_END("kij");
    assert_array_equals(C, D, N);

    PAPI_MEASURE_START("kji");
    SGEMM(k, j, i);
    PAPI_MEASURE_END("kji");
    assert_array_equals(C, D, N);
}