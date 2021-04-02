#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

void fib(mpz_t rez, int n) {

	// trivialni primer
	if(n == 0) {
		mpz_set_ui(rez, 0);
		return;
	}

	// alociranje prostora za konstantno matriko pri potenciranju matrike
	mpz_t** tab1 = (mpz_t**)malloc(sizeof(mpz_t*) * 2);
	for(int i=0; i<2; i++) {
		tab1[i] = (mpz_t*)malloc(sizeof(mpz_t) * 2);
		for(int j=0; j<2; j++) {
			mpz_init(tab1[i][j]);
		}
	}

	// konstantna matrika pri potenciranju matrike
	mpz_set_ui(tab1[0][0], 1);
	mpz_set_ui(tab1[0][1], 1);
	mpz_set_ui(tab1[1][0], 1);
	mpz_set_ui(tab1[1][1], 0);

	// alociranje prostora za spreminjajoco matriko pri potenciranju matrike
	mpz_t** tab2 = (mpz_t**)malloc(sizeof(mpz_t*) * 2);
	for(int i=0; i<2; i++) {
		tab2[i] = (mpz_t*)malloc(sizeof(mpz_t) * 2);
		for(int j=0; j<2; j++) {
			mpz_init(tab2[i][j]);
		}
	}

	// spreminjajoca matrika pri potenciranju matrike
	mpz_set_ui(tab2[0][0], 1);
	mpz_set_ui(tab2[0][1], 1);
	mpz_set_ui(tab2[1][0], 1);
	mpz_set_ui(tab2[1][1], 0);

	// spremenljivke za hranjenje vmesnih rezultatov
	mpz_t a, b, c, d;
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_init(d);

	mpz_t temp1, temp2;
	mpz_init(temp1);
	mpz_init(temp2);

	// izracun (n-1)-te potence zacetne matrike
	for(int i=0; i<n-2; i++) {
		mpz_mul(temp1, tab2[0][0], tab1[0][0]);
		mpz_mul(temp2, tab2[0][1], tab1[1][0]);
		mpz_add(a, temp1, temp2);

		mpz_mul(temp1, tab2[0][0], tab1[0][1]);
		mpz_mul(temp2, tab2[0][1], tab1[1][1]);
		mpz_add(b, temp1, temp2);

		mpz_mul(temp1, tab2[1][0], tab1[0][0]);
		mpz_mul(temp2, tab2[1][1], tab1[1][0]);
		mpz_add(c, temp1, temp2);

		mpz_mul(temp1, tab2[1][0], tab1[0][1]);
		mpz_mul(temp2, tab2[1][1], tab1[1][1]);
		mpz_add(d, temp1, temp2);

		mpz_set(tab2[0][0], a);
		mpz_set(tab2[0][1], b);
		mpz_set(tab2[1][0], c);
		mpz_set(tab2[1][1], d);
	}

	mpz_set(rez, tab2[0][0]);

	// sproscanje spremenljivk
	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			mpz_clear(tab1[i][j]);
		}
		free(tab1[i]);
	}
	free(tab1);

	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			mpz_clear(tab2[i][j]);
		}
		free(tab2[i]);
	}
	free(tab2);

	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	mpz_clear(d);

	mpz_clear(temp1);
	mpz_clear(temp2);

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
