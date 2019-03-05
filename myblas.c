#include <math.h>

void vectSqrt( int n, float* vect, float* result ) {
	for( int i = 0; i < n; i++ )
		result[i] = sqrt( vect[i] );
}
