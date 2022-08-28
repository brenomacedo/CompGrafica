#include "./matrix.h"

double scalarProduct (double* a, double* b, int n) {
    double result = 0;

    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }

    return result;
}