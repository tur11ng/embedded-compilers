#ifndef EMBEDDED_COMPILERS_EXERCISE_H
#define EMBEDDED_COMPILERS_EXERCISE_H

#ifndef EMBEDDED_COMPILERS_N
#error "EMBEDDED_COMPILERS_N must be defined"
#endif

#define LOOP(IMAX, VAR, ...) for (int VAR = 0; VAR < IMAX; VAR++) { __VA_ARGS__ }

#define SGEMM(I, J, K) \
    do { \
        LOOP(EMBEDDED_COMPILERS_N, I, \
            LOOP(EMBEDDED_COMPILERS_N, J, \
                LOOP(EMBEDDED_COMPILERS_N, K, \
                    C[j*EMBEDDED_COMPILERS_N+k] += A[j*EMBEDDED_COMPILERS_N+i] * B[i*EMBEDDED_COMPILERS_N+k]; \
                ) \
            ) \
        ) \
    } while(0)

#endif //EMBEDDED_COMPILERS_EXERCISE_H
