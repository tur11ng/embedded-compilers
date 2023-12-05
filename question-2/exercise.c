#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"

int main() {
    float A[N * N];
    float B[N * N];
    float C[N * N];

    fill_array(A);
    fill_array(B);
    fill_array(C);

    PAPI_INIT();

    PAPI_MEASURE_START("ijk");
    sgemm(i, j, k);
    PAPI_MEASURE_END("ijk");

    PAPI_MEASURE_START("ikj");
    sgemm(i, k, j);
    PAPI_MEASURE_END("ikj");

    PAPI_MEASURE_START("jik");
    sgemm(j, i, k);
    PAPI_MEASURE_END("jik");

    PAPI_MEASURE_START("jki");
    sgemm(j, k, i);
    PAPI_MEASURE_END("jki");

    PAPI_MEASURE_START("kij");
    sgemm(k, i, j);
    PAPI_MEASURE_END("kij");

    PAPI_MEASURE_START("kji");
    sgemm(k, j, i);
    PAPI_MEASURE_END("kji");
}