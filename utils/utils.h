#ifndef EMBEDDED_COMPILERS_UTILS_H
#define EMBEDDED_COMPILERS_UTILS_H

#include <stdlib.h>
#include <papi.h>

void fill_array(float array[]);
void copy_array(const float* src, float* dest, size_t size);
void assert_array_equals(const int* arr1, const int* arr2, size_t size);
void gemm(float *A, float *B, float *C, size_t size);

#define PAPI_INIT() \
    int retval = PAPI_library_init(PAPI_VER_CURRENT); \
    if (retval != PAPI_VER_CURRENT) { \
        fprintf(stderr, "PAPI error: %s\n", PAPI_strerror(retval)); \
        exit(1); \
    } \
    char errstring[PAPI_MAX_STR_LEN];

#define PAPI_MEASURE_START(region) \
    retval = PAPI_hl_region_begin(region); \
    if (retval != PAPI_OK) { \
        PAPI_perror("Error starting region measurement"); \
        exit(1); \
    }

#define PAPI_MEASURE_END(region) \
    retval = PAPI_hl_region_end(region); \
    if (retval != PAPI_OK) { \
        PAPI_perror("Error ending region measurement"); \
        exit(1); \
    }


#endif //EMBEDDED_COMPILERS_UTILS_H
