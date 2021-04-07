#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include "uthash.h"

// definicija strukture za hranjenje n-tega fibonaccijevega stevila
typedef struct fib_num fib_num;
struct fib_num {
	// spremenljivka n
	int n;
	// n-to fibonaccijevo stevilo
	mpz_t number;
	// handle, ki je dodan, da je strukturo mozno hashirati
	UT_hash_handle hh;
};

// spremenljivka za hranjenje konstante 0
mpz_t zero;
// kazalec na hash tabelo
struct fib_num *tab = NULL;

void fib(int n)	{
	
	// trivialni primeri
	if(n == 0)
		return;
	if(n == 1)
		return;
	
	// ustavitveni pogoj, ce je fib(n) ze izracunan
	struct fib_num *num;
	HASH_FIND_INT(tab, &n, num);
	if(num != NULL)
		return;

	// izracun predhodnjih dveh fibonaccijevih stevil
	fib(n-1);
	fib(n-2);

	// izracun n-tega fibonaccijevega stevila
	struct fib_num *num3 = (struct fib_num*)malloc(sizeof(struct fib_num));
	num3->n = n;
	mpz_init(num3->number);
	
	struct fib_num *num1;
	int n1 = n-1;
	HASH_FIND_INT(tab, &n1, num1);
	struct fib_num *num2;
	int n2 = n-2;
	HASH_FIND_INT(tab, &n2, num2);

	mpz_add(num3->number, num1->number, num2->number);
	HASH_ADD_INT(tab, n, num3);
	
}

int main() {

	// spremenljivka n za izracun fib(n)
	int n = 10;

	// definicija konstante 0
	mpz_init(zero);
	mpz_set_ui(zero, 0);
	
	// vstavljanje prvih dveh fibonaccijevih stevil v hash tabelo
	struct fib_num *num0 = (struct fib_num*)malloc(sizeof(struct fib_num));
	num0->n = 0;
	mpz_init(num0->number);
	mpz_set_ui(num0->number, 0);
	HASH_ADD_INT(tab, n, num0);

	struct fib_num *num1 = (struct fib_num*)malloc(sizeof(struct fib_num));
	num1->n = 1;
	mpz_init(num1->number);
	mpz_set_ui(num1->number, 1);
	HASH_ADD_INT(tab, n, num1);

	struct timespec startTime, endTime;
	// zacetni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);	

	fib(n);

	// koncni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);
	// izracun casa merjenja
	int timeElapsed = (endTime.tv_sec - startTime.tv_sec) * 1000 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000;

	// izpis rezultatov
	struct fib_num *rez;
	HASH_FIND_INT(tab, &n, rez);
	mpz_out_str(stdout, 10, rez->number);
	printf("\n");
	printf("cas: %d ms\n", timeElapsed);

	// sproscanje spremenljivk
	mpz_clear(zero);	
	struct fib_num *del;
	int d = 0;
	HASH_FIND_INT(tab, &d, del);
	HASH_DEL(tab, del);
	mpz_clear(del->number);
	free(del);
	d = 1;
	HASH_FIND_INT(tab, &d, del);
	HASH_DEL(tab, del);
	mpz_clear(del->number);
	free(del);

	for(int i=2; i<=n; i++) {
		HASH_FIND_INT(tab, &i, del);
		if(del != NULL) {
			HASH_DEL(tab, del);
			mpz_clear(del->number);
			free(del);
		}
	}

	return 0;

}
