import java.math.BigInteger;

public class fibonacci4 {
	
	static BigInteger fib(int n) {
		
		BigInteger a = new BigInteger("0");
		BigInteger b = new BigInteger("1");
		BigInteger c;
		
		// trivialni primer
		if(n == 0)
			return a;
		
		// iterativni izracun rezultata
		for(int i=0; i<n-1; i++) {
			c = b;
			b = b.add(a);
			a = c;
		}
		return b;
		
	}
	
	public static void main(String[] args) throws Exception {
		
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