// I, Ben Flowers, certify that this programming assignment reflects my own work,
// without the use of any external individuals (other than course/department staff ), generative-AI,
// or any other forbidden resources. I understand/accept the consequences of cheating as outlined
// in the course syllabus

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// linear function: y = ax + b 
double *linear_func(int a, int b, const double *values, int size) {
    double *output = (double *)malloc(size * sizeof(double));
    if (!output) return NULL;
    
    for (int i = 0; i < size; i++) {
        output[i] = a * values[i] + b;
    }
    return output;
}

// quadratic function: y = x^2 + ax + b 
double *quadratic_func(int a, int b, const double *values, int size) {
    double *output = (double *)malloc(size * sizeof(double));
    if (!output) return NULL;
    
    for (int i = 0; i < size; i++) {
        output[i] = values[i] * values[i] + a * values[i] + b;
    }
    return output;
}

// exponential function: y = e^(ax) + b
double *exp_func(int a, int b, const double *values, int size) {
    double *output = (double *)malloc(size * sizeof(double));
    if (!output) return NULL;
    
    for (int i = 0; i < size; i++) {
        output[i] = exp(a * values[i]) + b;
    }
    return output;
}

// sine function: y = a * sin(bx) 
double *sin_func(int a, int b, const double *values, int size) {
    double *output = (double *)malloc(size * sizeof(double));
    if (!output) return NULL;
    
    for (int i = 0; i < size; i++) {
        output[i] = a * sin(b * values[i]);
    }
    return output;
}

// derivative function with switch case 
double *func_derivative(const char *func, double *val_plus, double *val, double *val_minus,
                        int a, int b, int order, double h, int size) {
    double *output = (double *)malloc(size * sizeof(double));
    if (!output) return NULL;

    for (int i = 0; i < size; i++) {
        switch (order) {
            case 0:
                output[i] = val[i];
                break;
            case 1:
                output[i] = (val_plus[i] - val[i]) / h;
                break;
            case 2:
                output[i] = (val_plus[i] - 2 * val[i] + val_minus[i]) / (h * h);
                break;
            default:
                output[i] = 3.14159; // default case
                break;
        }
    }
    return output;
}

// ,ain method for obtaining values for function evaluation from command line arguments */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        // requires at least two arguments: values and the last one as "h"
        return 1;
    }

    // obtain the size of the array for values (argc - 2) and the value of h
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
