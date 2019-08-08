package il.co.ilrd.Complex;

public class ComplexTest {
	public static void main(String[] args) {
		Complex c1 = new Complex(3, 2);
		Complex c2 = new Complex(2, -3);
		Complex c3 = new Complex(0, -3);
		Complex c4 = new Complex(5, -1);
		Complex c5 = new Complex(1, 5);
		
		System.out.println("creating three complex numbers:");
		System.out.println("first: " + c1.toString());
		System.out.println("second: " + c2.toString());
		System.out.println("third: " + c3.toString());
		
		System.out.println("\nsetting the third complex with '5' instead of '-3':");
		c3.setImaginary(5);
		System.out.println("third: " + c3.toString());
		if(c3.getImaginary() == 5)
		{
			System.out.println("SUCSSES");
		}
		else
		{
			System.out.println("FAIL");
		}
		
		
		System.out.println("\nadding the first and second complex:");
		if(0 == c1.add(c2).compareTo(c4))
		{
			System.out.println("SUCSSES");
		}
		else
		{
			System.out.println("FAIL");
		}
		System.out.println("\nsubstracting the first and second complex:");
		if(0 == c1.add(c2).compareTo(c5))
		{
			System.out.println("SUCSSES");
		}
		else
		{
			System.out.println("FAIL");
		}
		
		System.out.println("\nisReal and isImaginary:");
		if(false == c3.isReal() && true == c3.isImaginary())
		{
			System.out.println("SUCSSES");
		}
		else
		{
			System.out.println("FAIL");
		}
		
		System.out.println("\ncomplex to string:");
		System.out.println("not a legal string:");
		Complex c6 = Complex.stringToComplex("123x  -55i");
		System.out.println(c6);
		
		System.out.println("legal string:");
		Complex c7 = Complex.stringToComplex("123  -55i");
		System.out.println(c7);
		
		System.out.println("just imaginary:");
		Complex c8 = Complex.stringToComplex("0 -55i");
		System.out.println(c8);
		
		System.out.println("just real:");
		Complex c9 = Complex.stringToComplex("123 +0i");
		System.out.println(c9);
	}

}
