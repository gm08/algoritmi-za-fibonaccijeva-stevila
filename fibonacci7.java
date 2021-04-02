import java.math.BigInteger;

public class fibonacci7 {
	
	// tabela za hranjenje fibonaccijevih stevil
	static BigInteger tab[];
	
	static void fib(int n) {
		
		// trivialni primeri
		if(n == 0) {
			tab[n] = new BigInteger("0");
			return;
		}
		
		if(n == 1 || n == 2){
			tab[n] = new BigInteger("1");
			return;
		}
		
		// ustavitveni pogoj, ce je fib(n) ze izracunan
		if(tab[n] != null)
			return;
		
		// izracun fib(n), ce je n sodo stevilo
		if(n % 2 == 0) {
			int k = n / 2;
			// f(n) = (2 * f(k-1) + f(k)) * f(k)
			fib(k);
			fib(k-1);
			tab[n] = (((new BigInteger("2")).multiply(tab[k-1])).add(tab[k])).multiply(tab[k]);
			return;
		}
		// izracun fib(n), ce je n liho stevilo
		else {
			int k = (n+1) / 2;
			// f(n) = f(k) * f(k) + f(k-1) * f(k-1)
			fib(k);
			fib(k-1);
			tab[n] = ((tab[k]).multiply(tab[k])).add((tab[k-1]).multiply(tab[k-1]));
			return;
		}
		
	}
	
	public static void main(String[] args) {

		// spremenljivka n za izracun fib(n)
		int n = 10;
		
		// inicializacija tabele
		tab = new BigInteger[n+1];
		
		// zacetni cas merjenja
		long startTime = System.currentTimeMillis();
		
		fib(n);
		
		// koncni cas merjenja
		long endTime = System.currentTimeMillis();
		// izracun casa merjenja
		long timeElapsed = endTime - startTime;
		
		// izpis rezultatov
		System.out.println(tab[n]);
		System.out.println("cas: "+timeElapsed+" ms");

	}
	
}