package il.co.ilrd.genericfactory;

public class genericTest {
	public static void main(String[] args)
	{
		shape myShape = new genericfactory<shape, circle>().create(new circle());
	}
}
