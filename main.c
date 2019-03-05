#include <stdio.h>
#include <stdlib.h>
#include "myblas.h"

const int N = 100000000;

int main() {
#ifdef __SSE__
	printf( "SSE flag is enabled by compiler.\r\n");
#endif
#ifdef __AVX__
	printf( "AVX flag is enabled by compiler.\r\n");
#endif

	float* arr1 = (float*) malloc( sizeof(float) * N );
	float* arr2 = (float*) malloc( sizeof(float) * N );

	vectSqrt( N, arr1, arr2 );

	return 1;
}
