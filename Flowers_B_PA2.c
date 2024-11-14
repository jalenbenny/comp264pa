// I, Ben Flowers, certify that this programming assignment reflects my own work,
// without the use of any external individuals (other than course/department staff ), generative-AI,
// or any other forbidden resources. I understand/accept the consequences of cheating as outlined
// in the course syllabus



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// functions with parameters a, b and input x
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

// calculate nth order derivative with central difference method 
double func_derivative(double (*fcn)(int, int, double), int order, double h, int a, int b, double x) {
    if (order == 0) return fcn(a, b, x);
    
    if (order == 1) {
        return (fcn(a, b, x + h) - fcn(a, b, x - h)) / (2 * h);  // central difference
    }
    
    if (order == 2) {
        return (fcn(a, b, x + h) - 2 * fcn(a, b, x) + fcn(a, b, x - h)) / (h * h);
    }
    
    return NAN;  // invalid order
}

// Compares two functions and their derivatives up to second order
double* func_equality(double (*fcnA)(int, int, double), double (*fcnB)(int, int, double),
                     double* x_values, int size, double tol) {
    double* result = malloc(size * 3 * sizeof(double));
    if (!result) return NULL;

    const double h = 0.001;
    const int a = 1, b = 1;

    for (int i = 0; i < size; i++) {
        double x = x_values[i];
        
        // Compare function values
        double fa = fcnA(a, b, x);
        double fb = fcnB(a, b, x);
        result[i * 3] = fabs(fa - fb) < tol ? 1.0 : 0.0;
        
        // Compare first derivatives
        double da = func_derivative(fcnA, 1, h, a, b, x);
        double db = func_derivative(fcnB, 1, h, a, b, x);
        result[i * 3 + 1] = fabs(da - db) < tol ? 1.0 : 0.0;
        
        // Compare second derivatives
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

// main method for obtaining values for function evaluation from command line arguments
int main(int argc, char *argv[]) {
    if (argc < 3) {
        // requires at least two arguments: values and the last one as "h"
        return 1;
    }

    // get the size of the array for values (argc - 2) and the value of h
    int size = argc - 2;
    double h = atof(argv[argc - 1]);
    
    // allocate dynamic arrays for x, x+h, and x-h
    double *x_values = malloc(size * sizeof(double));
    double *x_plus_h = malloc(size * sizeof(double));
    double *x_minus_h = malloc(size * sizeof(double));
    
    if (!x_values || !x_plus_h || !x_minus_h) {
        free(x_values);
        free(x_plus_h);
        free(x_minus_h);
        return 1;
    }
    
    // populate x_values and compute x+h and x-h arrays
    for (int i = 0; i < size; i++) {
        x_values[i] = atof(argv[i + 1]);
        x_plus_h[i] = x_values[i] + h;
        x_minus_h[i] = x_values[i] - h;
    }
    
    // clean up dynamic memory
    free(x_values);
    free(x_plus_h);
    free(x_minus_h);
    
    return 0;
}
