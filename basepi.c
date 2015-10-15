#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

double compute_pi(size_t dt)
{
	double pi= 0.0;
	double delta = 1.0/dt;
	for(size_t i=0; i<dt;i++){
		double x  = (double)i /dt;
		pi+= delta/(1.0+x*x);
	}
	return pi*4.0;



}

int main(int agrc, char* argv[]){


	size_t dt = 128000000;
	double piis = compute_pi(dt);
	printf("output = %20lf\n;",piis);
	return 0;


}
