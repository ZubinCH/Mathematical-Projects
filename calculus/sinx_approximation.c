#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define PI 3.1415926535

double power(double x, int n);
double f(double x);
double sink(double x);
double cosk(double x);

void print_array(double *arr, int len);


int main (void) {
    double sine_values[] = {sink(-12), sink(PI), sink(1), sink(5)};
    double cosine_values[] = {cosk(-12), cosk(PI), cosk(1), cosk(5)};
    double squared_values[] = {f(-12), f(PI), f(1), f(5)};

    printf("sine: ");
    print_array(sine_values, 4);

    printf("cosine: ");
    print_array(cosine_values, 4);

    printf("(cosx)^2 + (sinx)^2)");
    print_array(squared_values, 4);


    return 0;
}





void print_array(double *arr, int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%0.5f", arr[i]);
        if (i != len - 1) printf(", ");
    }
    printf("]\n");

}

double power(double x, int n) {
    double total = 1.0;

    for (int i = 0; i < n; i++) {
        total *= x;
    }

    return total;
}

double f(double x) {
    return sink(x) * sink(x) + cosk(x) * cosk(x);
}

double sink(double x) {
    double x1 = x;
    if (x > PI || x < -PI) {
        x1 = (x / (2 * PI) - floor(x / (2 * PI))) * 2 * PI;

        if (x1 > PI || x1 < -PI) {
            x1 = x1 - 2 * PI;
        }

    }
    

    return (x1 - power(x1, 3) / 6.0 + power(x1, 5) / 120.0 - power(x1, 7) / 5040.0 + power(x1, 9) / 362880.0 - power(x1, 11) / 39916800.0);

}


double cosk(double x) {
    double x1 = x;
    if (x > PI || x < -PI) {
        x1 = (x / (2 * PI) - floor(x / (2 * PI))) * 2 * PI;

        if (x1 > PI || x1 < -PI) {
            x1 = x1 - 2 * PI;
        }

    }
    

    return (1.0 - power(x1, 2) / 2.0 + power(x1, 4) / 24.0 - power(x1, 6) / 720.0 + power(x1, 8) / 40320.0 - power(x1, 10) / 3628800.0 + power(x1, 12) / 479001600.0);

}