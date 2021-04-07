#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// funkcija za pretvorbo iz znanstvene notacije v decimalno obliko
char *trimString(char *str1, mp_exp_t exp1) {
	char *rez;
	if(exp1 == 0) {
		rez = malloc(1 + 12);
		strcat(rez, "0");
	}
	else
		rez = malloc(exp1 + 12);
	strncpy(rez, str1, exp1);
	strcat(rez, ".");
	strncat(rez, str1+exp1, 10);
	return rez;
}

int main() {

	// kvadratni koren stevila 5
	mpf_t a;
	mpf_init2(a, 25);
	char *str = "2.23606797749978969640";
	mpf_set_str(a, str, 10);

	// inicializacija spremenljivk phi in phi2
	mpf_t phi, phi2;
	mpf_init2(phi, 25);
	mpf_init2(phi2, 25);
	
	// phi = (sqrt(5) + 1) / 2
	mpf_add_ui(phi, a, 1);
	mpf_div_ui(phi, phi, 2);
	
	// phi2 = 1 - phi
	mpf_ui_sub(phi2, 1, phi);

	// spremenljivka n za izracun fib(n)
	int n = 10;
	
	// formula, ki vrne tocen rezultat
	// fib(n) = (phi^n - phi2^n) / sqrt(5)
	mpf_t rez, temp;
	mpf_init2(rez, 25);
	mpf_init2(temp, 25);
	mpf_pow_ui(rez, phi, n);
	mpf_pow_ui(temp, phi2, n);
	mpf_sub(rez, rez, temp);
	mpf_div(rez, rez, a);
	// izpis rezultata v znanstveni notaciji
	mpf_out_str(stdout, 10, 0, rez);
	printf("\n");

	// enostavnejsa formula, ki za nizje n-je vrne priblizen rezultat
	// fib(n) = phi^n / sqrt(5)
	mpf_t rez2;
	mpf_init2(rez2, 25);
	mpf_pow_ui(rez2, phi, n);
	mpf_div(rez2, rez2, a);
	// izpis rezultata v znanstveni notaciji
	mpf_out_str(stdout, 10, 0, rez2);
	printf("\n");
	
	// spremenljivka za hranjenje mantise
	char *str1;
	// spremenljivka za hranjenje eksponenta
	mp_exp_t exp1;
	str1 = mpf_get_str (NULL, &exp1, 10, 0, rez2);
	
	// pretvorba iz znanstvene notacije v decimalno obliko
	char *rezultat = trimString(str1, exp1);
	// izpis rezultata v decimalni obliki
	printf("%s\n", rezultat);

	// sproscanje spremenljivk
	mpf_clear(a);
	mpf_clear(phi);
	mpf_clear(phi2);
	mpf_clear(rez);
	mpf_clear(temp);
	mpf_clear(rez2);

	return 0;	

}
