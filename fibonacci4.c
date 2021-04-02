#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <stdlib.h>

void fib(mpz_t rez, int n) {

	// inicializacija spremenljivk
	mpz_t a, b, c;
	mpz_init (a);
	mpz_init (b);
	mpz_init (c);
	mpz_set_ui(a, 0);
	mpz_set_ui(b, 1);

	// trivialni primer
	if(n == 0) {
		mpz_set(rez, a);
		mpz_clear(a);
		mpz_clear(b);
		mpz_clear(c);
		return;
	}

	// iterativni izracun rezultata	
	for(int i=0; i<n-1; i++) {
		mpz_set(c, b);
		mpz_add(b, b, a);
		mpz_set(a, c);
	}
	
	mpz_set(rez, b);
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);

}

int main() {
	
	// spremenljivka n za izracun fib(n)
	int n = 10;

	struct timespec startTime, endTime;
	// zacetni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);

	mpz_t rez;
	mpz_init(rez);
	fib(rez, n);

	// koncni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);
	// izracun casa merjenja
	int timeElapsed = (endTime.tv_sec - startTime.tv_sec) * 1000 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000;

	// izpis rezultatov
	mpz_out_str(stdout, 10, rez);
	printf("\n");
	printf("cas: %d ms\n", timeElapsed);

	mpz_clear(rez);

	return 0;	

}
