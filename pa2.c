#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double linear_func(int a, int b, double x) {
    return a * x + b;
}

double quadratic_func(int a, int b, double x) {
    return x * x + a * x + b;
}

double exp_func(int a, int b, double x) {
    return exp(a * x) + b;
}

double sin_func(int a, int b, double x) {
    return a * sin(b * x);
}

double func_comp(double (*fcnA)(int, int, double), double (*fcnB)(int, int, double), int a, int b, double x) {
    return fcnA(a, b, fcnB(a, b, x));
}

double func_derivative(double (*fcnA)(int, int, double), int order, double h, int a, int b, double x) {
    switch (order) {
        case 0:
            return fcnA(a, b, x);
        case 1:
            return (fcnA(a, b, x + h) - fcnA(a, b, x)) / h;
        case 2:
            return (fcnA(a, b, x + h) - 2 * fcnA(a, b, x) + fcnA(a, b, x - h)) / (h * h);
        default:
            return 3.14159;
    }
}

double* func_equality(double (*fcnA)(int, int, double), double (*fcnB)(int, int, double),
                      double* values, int size, double tol) {
    double* result = realloc(values, size * 3 * sizeof(double));
    if (result == NULL) {
        return NULL;
    }

    const double h = 0.001;
    const int a = 1, b = 1; // Example values for a and b

    for (int i = 0; i < size; i++) {
        double x = values[i];
        
        // Function values
        double fa = fcnA(a, b, x);
        double fb = fcnB(a, b, x);
        result[i * 3] = fabs(fa - fb) < tol ? 1.0 : 0.0;
        
        // First derivatives
        double da = func_derivative(fcnA, 1, h, a, b, x);
        double db = func_derivative(fcnB, 1, h, a, b, x);
        result[i * 3 + 1] = fabs(da - db) < tol ? 1.0 : 0.0;
        
        // Second derivatives
        double d2a = func_derivative(fcnA, 2, h, a, b, x);
        double d2b = func_derivative(fcnB, 2, h, a, b, x);
        result[i * 3 + 2] = fabs(d2a - d2b) < tol ? 1.0 : 0.0;
        
        if (fabs(fa - fb) >= tol) {
            free(result);
            return NULL;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    int size = argc - 1;
    double* values = malloc(sizeof(double));
    if (values == NULL) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        values[i] = atof(argc[i + 1]);
    }
    
    free(values);
    return 0;
}


