#ifndef EMBEDDED_COMPILERS_EXERCISE_H
#define EMBEDDED_COMPILERS_EXERCISE_H

#ifndef N
#error "N must be defined"
#endif

#define LOOP(IMAX, VAR, ...) for (int VAR = 0; VAR < IMAX; VAR++) { __VA_ARGS__ }

#define SGEMM(I, J, K) \
    do { \
        LOOP(N, I, \
            LOOP(N, J, \
                LOOP(N, K, \
                    C[j*N+k] += A[j*N+i] * B[i*N+k]; \
                ) \
            ) \
        ) \
    } while(0)

#endif //EMBEDDED_COMPILERS_EXERCISE_H
