import java.math.BigInteger;

public class fibonacci1 {
	
	static BigInteger fib(int n) {
		
		// ustavitvena pogoja za trivialna primera
		if(n == 0) {
			return new BigInteger("0");
		}
		else if(n == 1) {
			return new BigInteger("1");
		}
		// izracun preprostejsega primera fib(n-1) + fib(n-2)
		else {
			BigInteger b = fib(n-1).add(fib(n-2));
			return b;
		}
		
	}
	
	public static void main(String[] args) {
		
		// spremenljivka n za izracun fib(n)
		int n = 10;
		
		// zacetni cas merjenja
		long startTime = System.currentTimeMillis();
		
		BigInteger rez = fib(n);
		
		// koncni cas merjenja
		long endTime = System.currentTimeMillis();
		// izracun casa merjenja
		long timeElapsed = endTime - startTime;
		
		// izpis rezultatov
		System.out.println(rez);
		System.out.println("cas: "+timeElapsed+" ms");
		
	}
	
}