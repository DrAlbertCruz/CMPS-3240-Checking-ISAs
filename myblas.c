#include <math.h>
#include <immintrin.h>

/* VECTSQRT( integer n, single prec. array ptr a, single prec. array ptr b )
 * Steps through the elements of array `a`, carries out a square root, and 
 * stores the result into a separate array `b`. No input validation on the 
 * size of `b`. This function provides an example of how to compile a program
 * for use on machines that have AVX, SSE, or none at all. Note that these
 * are done at compile time. There isn't really anything preventing the user
 * from trying to run this program if their x86 processor doesn't support the
 * intrinsics.
 */
void vectSqrt( int n, float* vect, float* result ) {
	// Most compilers (gcc and clang) have flags that indicate the presense
	// of an ISA such as AVX or SSE. 
	#ifdef __AVX__
	// AVX `ymm` registers are 256 bits. They can fit 8 single prec. FPs.
	// Thus, we need i+=8.
	for( int i = 0; i < n; i+= 8 ) {
		// Further, POSIX (linux and mac) store memory differently from
		// windows. On POSIX machines you need to user storeu and loadu
		// intrinsic operations. You can detect POSIX with the __unix__
		// flag.
		//
		// The work flow for this operation is as follows:
		// 1) Load 8 values into ymm register
		// 2) Carry out sqrt on the packed ymm register
		// 3) Store 8 values into `result`
		#ifdef __unix__
		_mm256_storeu_ps( result + i, 
			_mm256_sqrt_ps( 
				_mm256_loadu_ps( vect + i )
			)
		);
		#else
		_mm256_store_ps( result + i, 
			_mm256_sqrt_ps( 
				_mm256_load_ps( vect + i )
			)
		);
		#endif
	}
	#elif __SSE__
	for( int i = 0; i < n; i+= 4 ) {
		#ifdef __unix__
		// Somewhat aggrevating that intel did not stick with a uniform
		// naming convention across different ISAs. You'll likely need
		// to refer to the Intel documentation to figure out other ops.
		//
		// https://software.intel.com/sites/landingpage/IntrinsicsGuide/
		_mm_storeu_ps( result + i, 
			_mm_sqrt_ps( 
				_mm_loadu_ps( vect + i )
			)
		);
		#else
		_mm_store_ps( result + i, 
			_mm_sqrt_ps( 
				_mm_load_ps( vect + i )
			)
		);
		#endif
	}
	#else
	for( int i = 0; i < n; i++ )
		result[i] = sqrt( vect[i] );
	#endif
}

void daxpy( int n, double a, double* x, double* y, double* result ) {
	for( int i = 0; i < n; i++ )
		result[i] = a * x[i] + y[i];
}
