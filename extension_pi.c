#include <immintrin.h>
#include <stdio.h>
double compute_pi(size_t dt)
{
	double pi =0.0;
	double delta = 1.0/dt;
	register __m256d ymm0, ymm1, ymm2, ymm3, ymm4;
	ymm0 = _mm256_set1_pd(1.0);
		//set ymm0 four block as 1.0

	ymm1 = _mm256_set1_pd(delta);
		//set ymm1 four block as delta
		
	ymm2 = _mm256_set_pd(delta * 3, delta*2, delta*1, 0.0);
		//set ymm2 as 3delta,2delta,delta,0

	ymm4 = _mm256_setzero_pd();
		//set ymm4 as zero

	for(int i=0; i<=dt -4; i += 4){

		ymm3 = _mm256_set1_pd(i*delta);
		//set ymm3 four block as delta*i 
		ymm3 = _mm256_add_pd(ymm3,ymm2);
		//a[3:0]+b[3:0]
		ymm3 = _mm256_mul_pd(ymm3,ymm3);
		//a[i]^2
		ymm3 = _mm256_add_pd(ymm0,ymm3);
		//a[i]+1.0
		ymm3 = _mm256_div_pd(ymm1,ymm3);
		//delta*1 / 1+x^2
		ymm4 = _mm256_add_pd(ymm4,ymm3);
	} 

	double tmp[4] __attribute__((aligned(32)));
	_mm256_store_pd(tmp,ymm4);
	pi += tmp[0]+tmp[1]+tmp[2]+tmp[3];

	return pi*4.0;
}


int main (int argc, char* argv[]){

	size_t dt = 128000000;

	double pi;
	pi = compute_pi(dt);

	printf("pi is %1.30lf\n",pi);
	return 0;

}
