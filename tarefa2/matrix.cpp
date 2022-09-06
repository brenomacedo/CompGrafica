#include <cmath>
#include "./matrix.h"

double scalarProduct (double* a, double* b, int n) {
    double result = 0;

    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }

    return result;
}

// norma do vetor
double magnitude (double* a, int n) {
    double squareOfMagnitude = 0;

    for (int i = 0; i < n; i++) {
        squareOfMagnitude += pow (a[i], 2.0);
    }

    return sqrt (squareOfMagnitude);
}

double max (double a, double b) {
    if (a > b) {
        return a;
    }

    return b;
}

double min (double a, double b) {
    if (a < b) {
        return a;
    }

    return b;
}