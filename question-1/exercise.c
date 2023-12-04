#include "../utils/utils.h"

#ifndef N
#error "N must be defined"
#endif

int main() {
    float A[N * N];
    float B[N * N];
    float C[N * N];

    fill_array(A);
    fill_array(B);
    fill_array(C);

    for (int k=0; k<N; k++) {
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}