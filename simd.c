/* Program to demonstrate SIMD vectorial computations vs normal scalar */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

int add_scalar(int size, int *a, int *b) 
{
    for (int i = 0; i < size; ++i) 
        a[i] += b[i];
}

int add_AVX(int size, int *a, int *b) 
{
    int i = 0;
    for (; i + 8 <= size; i += 8) 
    {
        // load 256-bit chunks of each array
        __m256i first_values = _mm256_loadu_si256((__m256i*) &a[i]);
        __m256i second_values = _mm256_loadu_si256((__m256i*) &b[i]);

        // add each pair of 32-bit integers in the 256-bit chunks
        first_values = _mm256_add_epi32(first_values, second_values);
        
        // store 256-bit chunk to first array
        _mm256_storeu_si256((__m256i*) &a[i], first_values);
    }
    // handle left overs
    for (; i < size; ++i) a[i] += b[i];
}

int main(int argc, char* argv[])
{
    char *input = argv[1];
    int size = atoi(input);

    printf("Generating arrays of size is %d\n\n", size);

    clock_t t;
    int* a;
    int* b;
    int i;

    a = (int*)malloc(size * sizeof(int));
    b = (int*)malloc(size * sizeof(int));

    if (a == NULL || b == NULL)
    {
        printf("Memory not allocated. \n");
        exit(0);
    }

    for (i = 0; i < size; ++i)
    {
        a[i] = i + 1;
        b[i] = 5;
    }
    
    // Calculate elapsed time with scalar addition 
    t = clock();
    add_scalar(size, a, b);
    t = clock() - t;
    double time_taken_scalar = ((double)t) / CLOCKS_PER_SEC;   
    printf("Scalar took %f seconds to execute \n", time_taken_scalar);

    // Calculate elapsed time with vector addition 
    t = clock();
    add_AVX(size, a, b);
    t = clock() - t;
    double time_taken_simd = ((double)t) / CLOCKS_PER_SEC;   
    printf("SIMD took %f seconds to execute \n", time_taken_simd);

    free(a);
    free(b);

    return 0;
}
