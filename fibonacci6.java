import java.math.BigInteger;

public class fibonacci6 {
	
	// spreminjajoca matrika pri potenciranju
	static BigInteger[][] tab;
	// konstantna matrika za potenciranje
	static BigInteger[][] tab0;
	
	// metoda za mnozenje dveh matrik
	static void mul(BigInteger[][] tab1, BigInteger[][] tab2) {
		
		BigInteger a = (tab1[0][0].multiply(tab2[0][0])).add(tab1[0][1].multiply(tab2[1][0]));
		BigInteger b = (tab1[0][0].multiply(tab2[0][1])).add(tab1[0][1].multiply(tab2[1][1]));
		BigInteger c = (tab1[1][0].multiply(tab2[0][0])).add(tab1[1][1].multiply(tab2[1][0]));
		BigInteger d = (tab1[1][0].multiply(tab2[0][1])).add(tab1[1][1].multiply(tab2[1][1]));
		
		tab1[0][0] = a;
		tab1[0][1] = b;
		tab1[1][0] = c;
		tab1[1][1] = d;
		
	}
	
	// metoda za rekurzivno potenciranje matrike
	static void pow(BigInteger[][] tab, int n) {
		
		// trivialni primer
		if(n == 1)
			return;

		// izracun (n / 2)-te potence matrike
		pow(tab, n / 2);
		// mnozenje (n / 2)-te potence matrike same s sabo
		mul(tab, tab);
		// primer, ko je n liho stevilo
		if(n % 2 != 0)
			mul(tab, tab0);
		
	}
	
	static BigInteger fib(int n) {
		
		// trivialni primer
		if(n == 0)
			return new BigInteger("0");
		
		// izracun (n-1)-te potence zacetne matrike
		if(n > 1)
			pow(tab, n-1);
		
		return tab[0][0]; 
		
	}
	
	public static void main(String[] args) {
		
		// spremenljivka n za izracun fib(n)
		int n = 10;
		
		//inicializacija zacetnih matrik
		tab = new BigInteger[2][2];
		tab[0][0] = new BigInteger("1");
		tab[0][1] = new BigInteger("1");
		tab[1][0] = new BigInteger("1");
		tab[1][1] = new BigInteger("0");
		
		tab0 = new BigInteger[2][2];
		tab0[0][0] = new BigInteger("1");
		tab0[0][1] = new BigInteger("1");
		tab0[1][0] = new BigInteger("1");
		tab0[1][1] = new BigInteger("0");
		
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