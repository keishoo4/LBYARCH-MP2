#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern float dot_product_c(float *vec1, float *vec2, int n);
extern void vec_product_asm(float *vec1, float *vec2, float *result, int n);

float get_time_elapsed(clock_t start)
{
    clock_t end = clock();
    return ((float)(end - start)) / (float)CLOCKS_PER_SEC;
}

int log2_int(unsigned int x) {
    int result = 0;
    while (x >>= 1) {
        result++;
    }
    return result;
}

int process(unsigned long long vec_size){
	unsigned long long n = vec_size;
	int exponent = (int)log2_int((unsigned int)n);

	float *vec1 = (float*)malloc(n * sizeof(float));
	float *vec2 = (float*)malloc(n * sizeof(float));
	if (vec1 == NULL || vec2 == NULL) {
		printf("Memory allocation failed! Reduce vector size.\n");
		return -1;
	}

	float result_c = 0.0f;
	float result_asm = 0.0f;
	
	// Generate random values for Vector 1
    for (size_t i = 0; i < n; i++) {
        vec1[i] = ((float)rand() / RAND_MAX) * 200.0f - 100.0f; // Random between -100.0 and 100.0
    }
    
	// Generate random values for Vector 2
    for (size_t i = 0; i < n; i++) {
        vec2[i] = ((float)rand() / RAND_MAX) * 200.0f - 100.0f; // Random between -100.0 and 100.0
    }
	
	// Start timing C implementation
	float total_time_c = 0.0f;
	printf("Starting dot product calculation (C) x20 for vector size 2^%d...\n", exponent);
	for (int t = 0; t < 20; t++) {
		clock_t start = clock();
		result_c = dot_product_c(vec1, vec2, (unsigned int)n);
		clock_t end = clock();
		total_time_c += ((float)(end - start)) / CLOCKS_PER_SEC;
	}
	float avg_time_c = total_time_c / 20.0f;

	// Start timing C implementation
	float total_time_asm = 0.0f;
	printf("Starting dot product calculation (Assembly) for vector size 2^%d...\n", exponent);
	for (int t = 0; t < 20; t++) {
		clock_t start = clock();
		vec_product_asm(vec1, vec2, &result_asm, (unsigned int)n);
		clock_t end = clock();
		total_time_asm += ((float)(end - start)) / CLOCKS_PER_SEC;
	}
	float avg_time_asm = total_time_asm / 20.0f;

	printf("\n=== RESULTS ===\n");
	printf("C Result:        %f\n", result_c);
	printf("Assembly Result: %f\n", result_asm);

	// Correctness Validation
	float diff = fabsf(result_c - result_asm);

	if (diff > 0.001f) {
		printf("WARNING: Results mismatch! Difference = %f\n", diff);
	} else {
		printf("Correctness Validation: Results match. Difference = %f\n", diff);
	}
	
	printf("\n=== PERFORMANCE ===\n");
	// printf("C Time:          %f seconds (%.3f microseconds)\n", execution_time_c, execution_time_c * 1000000);
	// printf("Assembly Time:   %f seconds (%.3f microseconds)\n", execution_time_asm, execution_time_asm * 1000000);
	
	printf("C Time:          %f seconds\n", avg_time_c);
	printf("Assembly Time:   %f seconds\n", avg_time_asm);

	// Free allocated memory
	free(vec1);
	free(vec2);
	
return 0;
}

int main(){
	int exponents[] = {20, 24, 30};
	int count = sizeof(exponents) / sizeof(exponents[0]);

	// Initialize random seed
	srand((unsigned int)time(NULL));

	for (int i = 0; i < count; ++i) {
		// int vec_size = (int)(1u << exponents[i]);
		unsigned long long vec_size = (1ULL << exponents[i]);
		printf("\n--- Running process for vector size 2^%d (n=%llu) ---\n", exponents[i], vec_size);
		int rc = process(vec_size);
		if (rc != 0) {
			printf("process returned %d for vector size 2^%d; continuing.\n", rc, exponents[i]);
		}
	}

	system("pause");
    
	return 0;
}


