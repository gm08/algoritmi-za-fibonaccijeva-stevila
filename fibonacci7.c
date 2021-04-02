#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

// spremenljivki, ki hranita konstanti 0 in 2
mpz_t zero;
mpz_t two;
// kazalec na tabelo za hranjenje fibonaccijevih stevil
mpz_t* tab;

void fib(mpz_t a, mpz_t b, int n) {

	// trivialni primeri
	if(n == 0) {
		return;
	}

	if(n == 1 || n == 2) {
		mpz_set_ui(tab[n], 1);
		return;
	}

	// ustavitveni pogoj, ce je fib(n) ze izracunan
	if(mpz_cmp(tab[n], zero) != 0)
		return;

	// izracun fib(n), ce je n sodo stevilo
	if(n % 2 == 0) {
		int k = n / 2;
		// f(n) = (2 * f(k-1) + f(k)) * f(k)
		fib(a, b, k);
		fib(a, b, k-1);
		mpz_mul(a, two, tab[k-1]);
		mpz_add(a, a, tab[k]);
		mpz_mul(tab[n], a, tab[k]);
		return;		
	}
	// izracun fib(n), ce je n liho stevilo
	else {
		int k = (n+1) / 2;
		// f(n) = f(k) * f(k) + f(k-1) * f(k-1)
		fib(a, b, k);
		fib(a, b, k-1);
		mpz_mul(a, tab[k], tab[k]);
		mpz_mul(b, tab[k-1], tab[k-1]);
		mpz_add(tab[n], a, b);
		return;
	}

}

int main() {

	// spremenljivka n za izracun fib(n)
	int n = 10;

	// inicializacija tabele
	tab = (mpz_t*)malloc(sizeof(mpz_t) * (n+1));
	for(int i=0; i<n+1; i++)
		mpz_init(tab[i]);

	// konstante, ki se uporabljajo pri izracunu formule
	mpz_init(zero);
	mpz_set_ui(zero, 0);
	mpz_init(two);
	mpz_set_ui(two, 2);
	
	struct timespec startTime, endTime;
	// zacetni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);

	// inicializacija spremenljivk za hranjenje vmesnih rezultatov pri izracunu
	mpz_t a, b;
	mpz_init(a);
	mpz_init(b);

	fib(a, b, n);

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
	mpz_clear(two);
	mpz_clear(a);
	mpz_clear(b);
	
	return 0;

}
