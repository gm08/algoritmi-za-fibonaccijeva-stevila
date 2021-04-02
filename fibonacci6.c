#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

// kazalec na spreminjajoco matriko pri potenciranju
mpz_t** tab;
// kazalec na konstantno matriko pri potenciranju
mpz_t** tab0;
// spremenljivke za hranjenje vmesnih rezultatov
mpz_t a, b, c, d, temp1, temp2;

// funkcija za mnozenje dveh matrik
void multiply(mpz_t** tab1, mpz_t** tab2) {

	mpz_mul(temp1, tab1[0][0], tab2[0][0]);
	mpz_mul(temp2, tab1[0][1], tab2[1][0]);
	mpz_add(a, temp1, temp2);

	mpz_mul(temp1, tab1[0][0], tab2[0][1]);
	mpz_mul(temp2, tab1[0][1], tab2[1][1]);
	mpz_add(b, temp1, temp2);

	mpz_mul(temp1, tab1[1][0], tab2[0][0]);
	mpz_mul(temp2, tab1[1][1], tab2[1][0]);
	mpz_add(c, temp1, temp2);

	mpz_mul(temp1, tab1[1][0], tab2[0][1]);
	mpz_mul(temp2, tab1[1][1], tab2[1][1]);
	mpz_add(d, temp1, temp2);

	mpz_set(tab1[0][0], a);
	mpz_set(tab1[0][1], b);
	mpz_set(tab1[1][0], c);
	mpz_set(tab1[1][1], d);

}

// funkcija za rekurzivno potenciranje matrike
void power(mpz_t** tab, int n) {
	
	// trivialni primer
	if(n == 1)
		return;

	// izracun (n / 2)-te potence matrike
	power(tab, n / 2);
	// mnozenje (n / 2)-te potence matrike same s sabo
	multiply(tab, tab);
	// primer, ko je n liho stevilo
	if(n % 2 != 0)
		multiply(tab, tab0);

}

void fib(mpz_t rez, int n) {
	
	// trivialni primer
	if(n == 0) {
		mpz_set_ui(rez, 0);
		return;
	}

	// izracun (n-1)-te potence zacetne matrike
	if(n > 1)
		power(tab, n - 1);
	
	mpz_set(rez, tab[0][0]);

}

int main() {
	
	// spremenljivka n za izracun fib(n)
	int n = 10;

	// inicializacija tabel
	tab = (mpz_t**)malloc(sizeof(mpz_t*) * 2);
	for(int i=0; i<2; i++) {
		tab[i] = (mpz_t*)malloc(sizeof(mpz_t) * 2);
		for(int j=0; j<2; j++) {
			mpz_init(tab[i][j]);
		}
	}
	
	mpz_set_ui(tab[0][0], 1);
	mpz_set_ui(tab[0][1], 1);
	mpz_set_ui(tab[1][0], 1);
	mpz_set_ui(tab[1][1], 0);

	tab0 = (mpz_t**)malloc(sizeof(mpz_t*) * 2);
	for(int i=0; i<2; i++) {
		tab0[i] = (mpz_t*)malloc(sizeof(mpz_t) * 2);
		for(int j=0; j<2; j++) {
			mpz_init(tab0[i][j]);
		}
	}
	
	mpz_set_ui(tab0[0][0], 1);
	mpz_set_ui(tab0[0][1], 1);
	mpz_set_ui(tab0[1][0], 1);
	mpz_set_ui(tab0[1][1], 0);

	// inicializacija spremenljvik za hranjenje vmesnih rezultatov
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_init(d);
	mpz_init(temp1);
	mpz_init(temp2);

	// inicializacija spremenljivke, ki hrani rezultat
	mpz_t rez;
	mpz_init(rez);

	struct timespec startTime, endTime;
	// zacetni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);	

	fib(rez, n);

	// koncni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);
	// izracun casa merjenja
	int timeElapsed = (endTime.tv_sec - startTime.tv_sec) * 1000 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000;

	// izpis rezultatov
	mpz_out_str(stdout, 10, rez);
	printf("\n");
	printf("cas: %d ms\n", timeElapsed);

	// sproscanje tabel
	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			mpz_clear(tab[i][j]);
		}
		free(tab[i]);
	}
	free(tab);

	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			mpz_clear(tab0[i][j]);
		}
		free(tab0[i]);
	}
	free(tab0);

	// sproscanje spremenljivk
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	mpz_clear(d);
	mpz_clear(temp1);
	mpz_clear(temp2);
	mpz_clear(rez);	

	return 0;

}
