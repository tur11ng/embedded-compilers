#ifndef EMBEDDED_COMPILERS_EXERCISE_H
#define EMBEDDED_COMPILERS_EXERCISE_H

#ifndef N
#error "N must be defined"
#endif

#define LOOP(IMAX, VAR, ...) for (int VAR = 0; VAR < IMAX; VAR++) { __VA_ARGS__ }

#define SGEMM(I, J, K) \
    do { \
        LOOP(10, I, \
            LOOP(10, J, \
                LOOP(10, K, \
                    C[j*N+k] = A[j*N+i] * B[i*N+k]; \
                ) \
            ) \
        ) \
    } while(0)

#endif //EMBEDDED_COMPILERS_EXERCISE_H
