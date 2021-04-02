import java.math.BigInteger;

public class fibonacci5 {
	
	static BigInteger fib(int n) {
		
		// trivialni primer
		if(n == 0) {
			return new BigInteger("0");
		}
		
		// konstantna matrika pri potenciranju matrike
		BigInteger[][] tab1 = new BigInteger[2][2];
		tab1[0][0] = new BigInteger("1");
		tab1[0][1] = new BigInteger("1");
		tab1[1][0] = new BigInteger("1");
		tab1[1][1] = new BigInteger("0");
		
		// spreminjajoca matrika pri potenciranju matrike
		BigInteger[][] tab2 = new BigInteger[2][2];
		tab2[0][0] = new BigInteger("1");
		tab2[0][1] = new BigInteger("1");
		tab2[1][0] = new BigInteger("1");
		tab2[1][1] = new BigInteger("0");
		
		// izracun (n-1)-te potence zacetne matrike
		for(int i=0; i<n-2; i++){
			BigInteger a = (tab2[0][0].multiply(tab1[0][0])).add(tab2[0][1].multiply(tab1[1][0]));
			BigInteger b = (tab2[0][0].multiply(tab1[0][1])).add(tab2[0][1].multiply(tab1[1][1]));
			BigInteger c = (tab2[1][0].multiply(tab1[0][0])).add(tab2[1][1].multiply(tab1[1][0]));
			BigInteger d = (tab2[1][0].multiply(tab1[0][1])).add(tab2[1][1].multiply(tab1[1][1]));
			
			tab2[0][0] = a;
			tab2[0][1] = b;
			tab2[1][0] = c;
			tab2[1][1] = d;
		}
		
		return tab2[0][0];
		
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