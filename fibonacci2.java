import java.math.BigInteger;

public class fibonacci2 {
	
	// tabela za hranjenje fibonaccijevih stevil
	static BigInteger tab[];
	
	static void fib(int n) {
		
		// trivialni primeri
		if(n == 0) {
			tab[n] = new BigInteger("0"); 
			return;
		}
		if(n == 1) {
			tab[n] = new BigInteger("1");
			return;
		}
		
		// ustavitveni pogoj, ce je fib(n) ze izracunan
		if(tab[n] != null)
			return;
		
		// izracun predhodnjih dveh fibonaccijevih stevil
		fib(n-1);
		fib(n-2);
		// izracun n-tega fibonaccijevega stevila
		tab[n] = tab[n-1].add(tab[n-2]);
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