#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

// spremenljivka, ki hrani konstanto 0
mpz_t zero;
// kazalec na tabelo za hranjenje fibonaccijevih stevil
mpz_t* tab;

void fib(int n) {
	
	// trivialni primeri
	if(n == 0)
		return;

	if(n == 1) {
		mpz_set_ui(tab[1], 1);
		return;
	}

	// ustavitveni pogoj, ce je fib(n) ze izracunan
	if(mpz_cmp(tab[n], zero) != 0)
		return;

	// izracun predhodnjih dveh fibonaccijevih stevil
	fib(n-1);
	fib(n-2);
	// izracun n-tega fibonaccijevega stevila
	mpz_add(tab[n], tab[n-1], tab[n-2]);

}

int main() {

	// spremenljivka n za izracun fib(n)
	int n = 10;

	// inicializacija tabele
	tab = (mpz_t*)malloc(sizeof(mpz_t) * (n+1));
	for(int i=0; i<n+1; i++)
		mpz_init(tab[i]);

	// inicializacija konstante 0
	mpz_init(zero);
	mpz_set_ui(zero, 0);
	

	struct timespec startTime, endTime;
	// zacetni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);	

	fib(n);

	// koncni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);
	// izracun casa merjenja
	int timeElapsed = (endTime.tv_sec - startTime.tv_sec) * 1000 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000;

	// izpis rezultatov
	mpz_out_str(stdout, 10, tab[n]);
	printf("\n");
	printf("cas: %d ms\n", timeElapsed);

	// sproscanje spremenljivk
	for(int i=0; i<n+1; i++)
		mpz_clear(tab[i]);
	free(tab);

	mpz_clear(zero);

	return 0;

}
