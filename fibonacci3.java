import java.math.BigInteger;
import java.util.*;

public class fibonacci3 {
	
	// hash tabela za hranjenje fibonaccijevih stevil
	static Hashtable<Integer, BigInteger> tab;
	
	static void fib(int n) {
		
		// trivialni primeri
		if(n == 0 || n == 1)
			return;
		
		// ustavitveni pogoj, ce je fib(n) ze izracunan
		if(tab.containsKey(n))
			return;
		
		// izracun predhodnjih dveh fibonaccijevih stevil
		fib(n-1);
		fib(n-2);
		// izracun n-tega fibonaccijevega stevila
		tab.put(n, (tab.get(n-1)).add(tab.get(n-2)));
		
	}
	
	public static void main(String[] args) {
	
		// spremenljivka n za izracun fib(n)
		int n = 10;
		
		// inicializacija hash tabele
		tab = new Hashtable<>(n+1, 0.75f);
		tab.put(0, new BigInteger("0"));
		tab.put(1, new BigInteger("1"));
		
		// zacetni cas merjenja
		long startTime = System.currentTimeMillis();
		
		fib(n);
		
		// koncni cas merjenja
		long endTime = System.currentTimeMillis();
		// izracun casa merjenja
		long timeElapsed = endTime - startTime;
		
		// izpis rezultatov
		System.out.println(tab.get(n));
		System.out.println("cas: "+timeElapsed+" ms");
	
	}
	
}