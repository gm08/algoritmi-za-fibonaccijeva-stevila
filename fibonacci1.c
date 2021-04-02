#include <stdio.h>
#include <gmp.h>
#include <time.h>

void fib(mpz_t rez, int n) {

	// ustavitvena pogoja za trivialna primera
	if(n == 0) {
		mpz_set_ui(rez, 0);
		return;
	}
	else if(n == 1) {
		mpz_set_ui(rez, 1);
		return;
	}
	// izracun preprostejsega primera fib(n-1) + fib(n-2)
	else {
		fib(rez, n-1);
		mpz_t a;
		mpz_init(a);
		mpz_set(a, rez);
		
		fib(rez, n-2);
		mpz_t b;
		mpz_init(b);
		mpz_set(b, rez);

		mpz_add(rez, a, b);
		mpz_clear(a);
		mpz_clear(b);
	}

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
