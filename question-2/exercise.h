#ifndef EMBEDDED_COMPILERS_EXERCISE_H
#define EMBEDDED_COMPILERS_EXERCISE_H

#ifndef N
#error "N must be defined"
#endif

#define sgemm(x, y, z) \
    do { \
        for (int x=0; x<N; x++) { \
            for (int y=0; y<N; y++) { \
                for (int z=0; z<N; z++) { \
                    C[y * N + z] += A[y * N + x] * B[x * N + z]; \
                } \
            } \
        } \
    } while(0)

#endif //EMBEDDED_COMPILERS_EXERCISE_H
