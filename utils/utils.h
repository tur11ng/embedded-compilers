#ifndef EMBEDDED_COMPILERS_UTILS_H
#define EMBEDDED_COMPILERS_UTILS_H

#include <stdlib.h>
#include <papi.h>

void fill_array(float array[]);

#define PAPI_INIT() \
    do { \
        int retval; \
        char errstring[PAPI_MAX_STR_LEN]; \
    } while(0)

#define PAPI_MEASURE_START(region) \
    do { \
        retval = PAPI_hl_region_begin(region); \
        if ( retval != PAPI_OK ) { \
            fprintf(stderr, "Error: %s\n", errstring); \
            exit(1); \
        } \
    } while (0)

#define PAPI_MEASURE_END(region) \
    retval = PAPI_hl_region_end(region); \
    if ( retval != PAPI_OK ) { \
        fprintf(stderr, "Error: %s\n", errstring); \
        exit(1); \
    }

#endif //EMBEDDED_COMPILERS_UTILS_H
