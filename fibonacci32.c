#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

// spremenljvika za hranjenje stevila bucketov
int m;
mpz_t sum;

// definicija strukture za hranjenje n-tega fibonaccijevega stevila
typedef struct fib_num fib_num;
struct fib_num {
	// spremenljivka n
	int n;
	// n-to fibonaccijevo stevilo
	mpz_t number;
	fib_num* next;
};

// definicija strukture za hranjenje hash tabele
typedef struct HashTable HashTable;
struct HashTable {
	fib_num** nums;
};

// funkcija za kreiranje hash tabele
HashTable* create_tab() {
	// alociranje prostora za m bucketov
	HashTable* tab = (HashTable*)malloc(sizeof(HashTable));
	tab->nums = (fib_num**)malloc(sizeof(fib_num*) * m);
	for(int i=0; i<m; i++) {
		tab->nums[i] = NULL;
	}

	return tab;
}

// hash funkcija
// TODO implementacija boljse hash funkcije
int hash(int n) {
	int a = (n*(n+3)) % m;
	return a;
}

// funkcija za sproscanje hash tabele
void free_tab(HashTable* tab) {
	for(int i=0; i<m; i++) {
		fib_num* num = tab->nums[i];
		fib_num* temp;
		while(num != NULL) {
			temp = num;
			num = num->next;
			mpz_clear(temp->number);
			free(temp);
		}
	}
	free(tab->nums);
	free(tab);
}

// funkcija za vstavljanje elementa v hash tabelo
void insert(HashTable* tab, int n, mpz_t number) {
	
	// kreiranje nove strukture
	fib_num* num = (fib_num*)malloc(sizeof(fib_num));
	num->n = n;
	mpz_init(num->number);
	mpz_set(num->number, number);
	num->next = NULL;

	// izracun hash indexa
	int index = hash(n);

	// vstavljanje v hash tabelo
	fib_num* num1 = tab->nums[index];
	if(num1 == NULL) {
		tab->nums[index] = num;
	}	
	// obravnavanje kolizije
	else {
		while(1) {
			if(num1->next == NULL) {
				num1->next = num;
				break;
			}
			num1 = num1->next;
		}
	}
	
}

// funkcija za vracanje elementa iz hash tabele
fib_num* find(HashTable* tab, int n) {
	int index = hash(n);
	fib_num* num = tab->nums[index];
	while(num != NULL) {
		if(num->n == n)
			return num;
		num = num->next;			
	}
	return NULL;
}

void fib(HashTable* tab, int n) {

	// trivialni primeri
	if(n == 0 || n == 1)
		return;

	// ustavitveni pogoj, ce je fib(n) ze izracunan
	fib_num* num = find(tab, n);
	if(num != NULL)
		return;
	
	// izracun predhodnjih dveh fibonaccijevih stevil
	fib(tab, n-1);
	fib(tab, n-2);
	
	// izracun n-tega fibonaccijevega stevila
	fib_num* num1 = find(tab, n-1);
	fib_num* num2 = find(tab, n-2);
	
	mpz_add(sum, num1->number, num2->number);
	insert(tab, n, sum);
}

int main() {
	
	// stevilo bucketov v hash tabeli
	m = 11;
	// spremenljivka n za izracun fib(n)
	int n = 10;
	// kreiranje hash tabele in vstavljanje prvih dveh fibonaccijevih stevil
	HashTable* tab = create_tab(n);
	mpz_t a;
	mpz_init(a);
	mpz_set_ui(a, 0);
	insert(tab, 0, a);
	mpz_set_ui(a, 1);
	insert(tab, 1, a);
	mpz_clear(a);

	mpz_init(sum);

	struct timespec startTime, endTime;
	// zacetni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);	

	fib(tab, n);

	// koncni cas merjenja
	clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);
	// izracun casa merjenja
	int timeElapsed = (endTime.tv_sec - startTime.tv_sec) * 1000 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000;
	
	// izpis rezultatov
	mpz_out_str(stdout, 10, find(tab, n)->number);
	printf("\n");
	printf("cas: %d ms\n", timeElapsed);

	free_tab(tab);
	mpz_clear(sum);

	return 0;
	
}
