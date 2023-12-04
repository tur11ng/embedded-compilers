#include "../utils/utils.h"

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

int main() {
    srand(time(NULL));

    float A[N * N];
    float B[N * N];
    float C[N * N];

    fill_array(A);
    fill_array(B);
    fill_array(C);

#ifdef ijk
    sgemm(i, j, k);
#elif ikj
    sgemm(i, k, j);
#elif jik
    sgemm(j, i, k);
#elif jki
    sgemm(j, k, i);
#elif kij
    sgemm(k, i, j);
#elif kji
    sgemm(k, j, i);
#endif
}