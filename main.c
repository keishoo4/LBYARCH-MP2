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

int main (){
	int n;
	
	// Initialize random seed
	srand(time(NULL));
	
	printf("Enter Vector Length:");
	scanf("%d", &n);
	

	float *vec1 = (float*)malloc(n * sizeof(float));
	float *vec2 = (float*)malloc(n * sizeof(float));
	float result_c = 0.0;
	float result_asm = 0.0;

	
	
	// Generate random values for Vector 1
    for (int i = 0; i < n; i++) {
        vec1[i] = ((float)rand() / RAND_MAX) * 200.0f - 100.0f; // Random between -100.0 and 100.0

    }
    
	// Generate random values for Vector 2
    for (int i = 0; i < n; i++) {
        vec2[i] = ((float)rand() / RAND_MAX) * 200.0f - 100.0f; // Random between -100.0 and 100.0
    }
	
	// Start timing C implementation
	printf("Starting dot product calculation (C)...\n");
	clock_t start_time_c = clock();
	
	// Perform single dot product calculation (C)
	result_c = dot_product_c(vec1, vec2, n);
	
	clock_t end_time_c = clock();
	float execution_time_c = ((float)(end_time_c - start_time_c)) / CLOCKS_PER_SEC;

	printf("Starting dot product calculation (Assembly)...\n");
	clock_t start_time_asm = clock();

	// Perform single dot product calculation (Assembly)
	vec_product_asm(vec1, vec2, &result_asm, n);

	clock_t end_time_asm = clock();
	float execution_time_asm = ((float)(end_time_asm - start_time_asm)) / CLOCKS_PER_SEC;

	printf("\n=== RESULTS ===\n");
	printf("C Result:        %f\n", result_c);
	printf("Assembly Result: %f\n", result_asm);
	
	printf("\n=== PERFORMANCE ===\n");
	printf("C Time:          %f seconds (%.3f microseconds)\n", execution_time_c, execution_time_c * 1000000);
	printf("Assembly Time:   %f seconds (%.3f microseconds)\n", execution_time_asm, execution_time_asm * 1000000);
	
	// Free allocated memory
	free(vec1);
	free(vec2);

	system("pause");
	
	
return 0;
}


