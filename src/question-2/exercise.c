#include <stdio.h>
#include <stdlib.h>

#include "exercise.h"
#include "../utils/utils.h"

int main() {
    float A[EMBEDDED_COMPILERS_N * EMBEDDED_COMPILERS_N] = {0};
    float B[EMBEDDED_COMPILERS_N * EMBEDDED_COMPILERS_N] = {0};
    float C[EMBEDDED_COMPILERS_N * EMBEDDED_COMPILERS_N] = {0};

    float D[EMBEDDED_COMPILERS_N * EMBEDDED_COMPILERS_N] = {0};

    fill_array(A);
    fill_array(B);
    fill_array(C);

    PAPI_INIT();

    PAPI_MEASURE_START("ijk");
    SGEMM(i, j, k);
    PAPI_MEASURE_END("ijk");

    PAPI_MEASURE_START("ikj");
    SGEMM(i, k, j);
    PAPI_MEASURE_END("ikj");

    PAPI_MEASURE_START("jik");
    SGEMM(j, i, k);
    PAPI_MEASURE_END("jik");

    PAPI_MEASURE_START("jki");
    SGEMM(j, k, i);
    PAPI_MEASURE_END("jki");

    PAPI_MEASURE_START("kij");
    SGEMM(k, i, j);
    PAPI_MEASURE_END("kij");

    PAPI_MEASURE_START("kji");
    SGEMM(k, j, i);
    PAPI_MEASURE_END("kji");
}