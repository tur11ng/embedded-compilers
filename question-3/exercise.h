#ifndef EMBEDDED_COMPILERS_EXERCISE_H
#define EMBEDDED_COMPILERS_EXERCISE_H

#ifndef N
#error "N must be defined"
#endif

#ifndef BLOCK_SIZE
#error "BLOCK_SIZE must be defined"
#endif

#ifndef L1_CACHE_LINE_SIZE // Or sysconf (_SC_LEVEL1_DCACHE_LINESIZE)
#error "L1_CACHE_LINE_SIZE must be defined"
#endif

#endif //EMBEDDED_COMPILERS_EXERCISE_H
