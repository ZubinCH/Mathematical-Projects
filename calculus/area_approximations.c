#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define RECTS 2000
#define A 1
#define B 7

double f(double x);
double power(double x, int n);
double approx(double a, double b, int n);



int main(void) {
    double area = approx(A, B, RECTS);

    printf("%0.10f\n", area);
}

double power(double x, int n) {
    double total = 1.0;

    for (int i = 0; i < n; i++) {
        total *= x;
    }

    return total;
}

double f(double x) {
    return power(x, 3) + 2 * power(x, 2) + x + 5;
}

double approx(double a, double b, int n) {
    double sum = (f(a) + f(b)) / 2.0;
    double dx = (b - a) / n;

    for (int i = 1; i < n; i++) {
        sum += f(dx * i + a);
    }

    return dx * sum;
}