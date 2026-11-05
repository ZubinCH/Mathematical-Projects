#include <stdio.h>
#include <stdlib.h>


double *division (int length, double arr[], int ddegree, double d_arr[]);
double *divide_step (double reading_arr[], int ddegree, double d_arr[]);

double *construct_array(int pdegree, double p_array[], int ddegree);

void print_arr (int len, double arr[]);


int main(void) {
    int poly_degree = 5;
    double poly_arr[] = {1, 0, 0, 0, 0, -1};
    
    // double array[] = {4, 2, 3, -2, 1, -3, 0, 0, 0, 0};

    int divisor_degree = 1;
    double divisor[] = {1, -1};

    int length = poly_degree + 2 + divisor_degree + 1;
    double *array = construct_array(poly_degree, poly_arr, divisor_degree);

    double *result = division(length, array, divisor_degree, divisor);

    int remainder_degree = result[0];
    double remainder[remainder_degree + 1];
    for (int i = 0; i < remainder_degree + 1; i++) {
        remainder[i] = result[i + 1];
    }
    
    int quotient_degree = (int) array[0] - divisor_degree;
    double quotient[quotient_degree + 1];
    for (int i = 0; i < quotient_degree + 1; i++) {
        quotient[i] = result[length - divisor_degree - quotient_degree - 2 + i];
    }


    printf("\n");
    printf("Quotient polynomial:\n");
    printf("    Degree: %i\n", quotient_degree);
    printf("    Polynomial: ");
    print_arr(quotient_degree + 1, quotient);

    printf("\n");
    printf("Remainder polynomial:\n");
    printf("    Degree: %i\n", remainder_degree);
    printf("    Polynomial: ");
    print_arr(remainder_degree + 1, remainder);
    printf("\n");

    print_arr(length - divisor_degree - 1, result);


    free(array);
    free(result);
    return 0;
}

/* 
    
    Pseudocode:

        1. look at base case of the function
        2. split array into substituent components
        3. determine the degree of the returned polynomial


        4. divide first term of the polynomial by the first term of the divisor and store that value as the first coefficient of the quotient
        5. multiply the coefficients of the divisor by the returned scaling value
        6. substract the terms of the polynomial by the scaled divisor

        7. place the (n + 1)th term into the new array

*/ 


// arr structure: {pdegree, p_arr[], q_arr[]}

double *division (int length, double arr[], int ddegree, double d_arr[]) {
    if (arr[0] < ddegree) {
        return arr;
    }

    // Initialise polynomial degrees and arrays
    int pdegree = arr[0];
    int qdegree = pdegree - ddegree;
    double p_arr[pdegree + 2];
    double reading_arr[ddegree + 1];
    double q_arr[qdegree + 1];

    // Make p_arr and reading_arr
    for (int i = 0; i < pdegree + 2; i++) {
        p_arr[i] = arr[i + 1];

        if (i < ddegree + 1) {
            reading_arr[i] = arr[i + 1];
        }
    }

    // Iterate division
    for (int i = 0; i < qdegree + 1; i++) {
        double *division_result = divide_step(reading_arr, ddegree, d_arr);
        q_arr[i] = division_result[0];

        for (int j = 0; j < ddegree; j++) {
            reading_arr[j] = division_result[j + 2];
        }
        reading_arr[ddegree] = p_arr[ddegree + 1 + i];
        free(division_result);
    }


    // Store division result in new array
    double *new_arr = malloc(sizeof(double)*(length - ddegree - 1));
    if (!new_arr) {
        printf("Memory allocation failed.\n");
        return arr;
    }
    new_arr[0] = ddegree - 1;
    for (int i = 0; i < new_arr[0] + 1; i++) {
        new_arr[i + 1] = reading_arr[i];
    }
    for (int i = 0; i < qdegree + 1; i++) {
        new_arr[ddegree + 1 + i] = q_arr[i];
    }


    return new_arr;
}

// return value: {scale_factor, 0, new_polynomial[]

double *divide_step (double reading_arr[], int ddegree, double d_arr[]) {
    
    double *new_arr = malloc(sizeof(double)*(ddegree + 2));
    if (!new_arr) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    double scale_factor = reading_arr[0] / d_arr[0];
    new_arr[0] = scale_factor;

    double scaled_d_arr[ddegree + 1];
    for (int i = 0; i < ddegree + 1; i++) {
        scaled_d_arr[i] = scale_factor * d_arr[i];
        new_arr[i + 1] = reading_arr[i] - scaled_d_arr[i];
    }

    return new_arr;
}


double *construct_array(int pdegree, double p_array[], int ddegree) {
    double *array = calloc(pdegree + 2 + ddegree + 1, sizeof(double));
    array[0] = (double) pdegree;

    for (int i = 0; i < pdegree + 1; i++) {
        array[i + 1] = p_array[i];
    }

    return array;
}



void print_arr(int len, double arr[]) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%0.f", arr[i]);
        if (i != len - 1) printf(", ");
    }
    printf("]\n");

}