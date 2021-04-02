import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;

public class fibonacci8 {
	public static void main(String[] args) {
		
		// kvadratni koren stevila 5
		// izracun korena s funkcijo sqrt, ce je verzija Jave >= 9
		// BigDecimal a = new BigDecimal("5");
		// MathContext mc = new MathContext(20);
		// a = a.sqrt(mc);
		// direktna inicializacija spremenljivke z vrednostjo kvadratnega korena stevila 5
		BigDecimal a = new BigDecimal("2.23606797749978969640");
		
		// konstanti 1 in 2
		BigDecimal b = new BigDecimal("1");
		BigDecimal c = new BigDecimal("2");
		
		// phi = (sqrt(5) + 1) / 2
		BigDecimal phi = (a.add(b)).divide(c);
		
		// phi2 = 1 - phi
		BigDecimal phi2 = b.subtract(phi);
		
		// spremenljivka n za izracun fib(n)
		int n = 10;
		
		// formula, ki vrne tocen rezultat
		// fib(n) = (phi^n - phi2^n) / sqrt(5)	
		BigDecimal rez = phi.pow(n).subtract(phi2.pow(n)).divide(a, 10, RoundingMode.HALF_UP);
		System.out.println(rez);
		
		// enostavnejsa formula, ki za nizje n-je vrne priblizen rezultat
		// fib(n) = phi^n / sqrt(5)
		BigDecimal rez2 = phi.pow(n).divide(a, 10, RoundingMode.HALF_UP);
		System.out.println(rez2);
		
	}
}